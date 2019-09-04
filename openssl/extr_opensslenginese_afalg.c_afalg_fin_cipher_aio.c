#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct iocb {int aio_fildes; size_t aio_buf; size_t aio_nbytes; int /*<<< orphan*/  aio_resfd; int /*<<< orphan*/  aio_flags; scalar_t__ aio_data; scalar_t__ aio_offset; int /*<<< orphan*/  aio_lio_opcode; } ;
struct io_event {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  eval ;
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  aio_ctx; int /*<<< orphan*/  efd; struct iocb* cbt; } ;
typedef  TYPE_1__ afalg_aio ;

/* Variables and functions */
 int /*<<< orphan*/  ALG_PERR (char*,char*,int,...) ; 
 int /*<<< orphan*/  ALG_PWARN (char*,char*,int) ; 
 int /*<<< orphan*/  ALG_WARN (char*,char*,int,...) ; 
 int /*<<< orphan*/  ASYNC_pause_job () ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  IOCB_CMD_PREAD ; 
 int /*<<< orphan*/  IOCB_FLAG_RESFD ; 
 int MAX_INFLIGHTS ; 
 scalar_t__ MODE_UNINIT ; 
 int afalg_setup_async_event_notification (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int io_getevents (int /*<<< orphan*/ ,int,int,struct io_event*,struct timespec*) ; 
 int io_read (int /*<<< orphan*/ ,int,struct iocb**) ; 
 int /*<<< orphan*/  memset (struct iocb*,char,int) ; 
 int read (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int afalg_fin_cipher_aio(afalg_aio *aio, int sfd, unsigned char *buf,
                                size_t len)
{
    int r;
    int retry = 0;
    unsigned int done = 0;
    struct iocb *cb;
    struct timespec timeout;
    struct io_event events[MAX_INFLIGHTS];
    u_int64_t eval = 0;

    timeout.tv_sec = 0;
    timeout.tv_nsec = 0;

    /* if efd has not been initialised yet do it here */
    if (aio->mode == MODE_UNINIT) {
        r = afalg_setup_async_event_notification(aio);
        if (r == 0)
            return 0;
    }

    cb = &(aio->cbt[0 % MAX_INFLIGHTS]);
    memset(cb, '\0', sizeof(*cb));
    cb->aio_fildes = sfd;
    cb->aio_lio_opcode = IOCB_CMD_PREAD;
    /*
     * The pointer has to be converted to unsigned value first to avoid
     * sign extension on cast to 64 bit value in 32-bit builds
     */
    cb->aio_buf = (size_t)buf;
    cb->aio_offset = 0;
    cb->aio_data = 0;
    cb->aio_nbytes = len;
    cb->aio_flags = IOCB_FLAG_RESFD;
    cb->aio_resfd = aio->efd;

    /*
     * Perform AIO read on AFALG socket, this in turn performs an async
     * crypto operation in kernel space
     */
    r = io_read(aio->aio_ctx, 1, &cb);
    if (r < 0) {
        ALG_PWARN("%s(%d): io_read failed : ", __FILE__, __LINE__);
        return 0;
    }

    do {
        /* While AIO read is being performed pause job */
        ASYNC_pause_job();

        /* Check for completion of AIO read */
        r = read(aio->efd, &eval, sizeof(eval));
        if (r < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                continue;
            ALG_PERR("%s(%d): read failed for event fd : ", __FILE__, __LINE__);
            return 0;
        } else if (r == 0 || eval <= 0) {
            ALG_WARN("%s(%d): eventfd read %d bytes, eval = %lu\n", __FILE__,
                     __LINE__, r, eval);
        }
        if (eval > 0) {

            /* Get results of AIO read */
            r = io_getevents(aio->aio_ctx, 1, MAX_INFLIGHTS,
                             events, &timeout);
            if (r > 0) {
                /*
                 * events.res indicates the actual status of the operation.
                 * Handle the error condition first.
                 */
                if (events[0].res < 0) {
                    /*
                     * Underlying operation cannot be completed at the time
                     * of previous submission. Resubmit for the operation.
                     */
                    if (events[0].res == -EBUSY && retry++ < 3) {
                        r = io_read(aio->aio_ctx, 1, &cb);
                        if (r < 0) {
                            ALG_PERR("%s(%d): retry %d for io_read failed : ",
                                     __FILE__, __LINE__, retry);
                            return 0;
                        }
                        continue;
                    } else {
                        /*
                         * Retries exceed for -EBUSY or unrecoverable error
                         * condition for this instance of operation.
                         */
                        ALG_WARN
                            ("%s(%d): Crypto Operation failed with code %lld\n",
                             __FILE__, __LINE__, events[0].res);
                        return 0;
                    }
                }
                /* Operation successful. */
                done = 1;
            } else if (r < 0) {
                ALG_PERR("%s(%d): io_getevents failed : ", __FILE__, __LINE__);
                return 0;
            } else {
                ALG_WARN("%s(%d): io_geteventd read 0 bytes\n", __FILE__,
                         __LINE__);
            }
        }
    } while (!done);

    return 1;
}