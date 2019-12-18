#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct aiocb {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_21__ {struct TYPE_21__* data; } ;
struct TYPE_17__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  log; TYPE_8__ name; TYPE_5__* aio; } ;
typedef  TYPE_3__ ngx_file_t ;
struct TYPE_18__ {int active; scalar_t__ complete; scalar_t__ ready; int /*<<< orphan*/  handler; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_15__ {TYPE_4__* sival_ptr; } ;
struct TYPE_16__ {TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_notify; int /*<<< orphan*/  sigev_notify_kqueue; } ;
struct TYPE_20__ {size_t aio_nbytes; TYPE_2__ aio_sigevent; int /*<<< orphan*/ * aio_buf; int /*<<< orphan*/  aio_offset; int /*<<< orphan*/  aio_fildes; } ;
struct TYPE_19__ {scalar_t__ err; int /*<<< orphan*/  file; TYPE_7__ aiocb; int /*<<< orphan*/  nbytes; TYPE_4__ event; } ;
typedef  TYPE_5__ ngx_event_aio_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int NGX_EAGAIN ; 
 int NGX_ENOSYS ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  SIGEV_KEVENT ; 
 int aio_read (TYPE_7__*) ; 
 int ngx_errno ; 
 scalar_t__ ngx_file_aio ; 
 int /*<<< orphan*/  ngx_file_aio_event_handler ; 
 scalar_t__ ngx_file_aio_init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_file_aio_result (int /*<<< orphan*/ ,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_kqueue ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,size_t,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ngx_read_file (TYPE_3__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_set_errno (scalar_t__) ; 

ssize_t
ngx_file_aio_read(ngx_file_t *file, u_char *buf, size_t size, off_t offset,
    ngx_pool_t *pool)
{
    int               n;
    ngx_event_t      *ev;
    ngx_event_aio_t  *aio;

    if (!ngx_file_aio) {
        return ngx_read_file(file, buf, size, offset);
    }

    if (file->aio == NULL && ngx_file_aio_init(file, pool) != NGX_OK) {
        return NGX_ERROR;
    }

    aio = file->aio;
    ev = &aio->event;

    if (!ev->ready) {
        ngx_log_error(NGX_LOG_ALERT, file->log, 0,
                      "second aio post for \"%V\"", &file->name);
        return NGX_AGAIN;
    }

    ngx_log_debug4(NGX_LOG_DEBUG_CORE, file->log, 0,
                   "aio complete:%d @%O:%uz %V",
                   ev->complete, offset, size, &file->name);

    if (ev->complete) {
        ev->complete = 0;
        ngx_set_errno(aio->err);

        if (aio->err == 0) {
            return aio->nbytes;
        }

        ngx_log_error(NGX_LOG_CRIT, file->log, ngx_errno,
                      "aio read \"%s\" failed", file->name.data);

        return NGX_ERROR;
    }

    ngx_memzero(&aio->aiocb, sizeof(struct aiocb));

    aio->aiocb.aio_fildes = file->fd;
    aio->aiocb.aio_offset = offset;
    aio->aiocb.aio_buf = buf;
    aio->aiocb.aio_nbytes = size;
#if (NGX_HAVE_KQUEUE)
    aio->aiocb.aio_sigevent.sigev_notify_kqueue = ngx_kqueue;
    aio->aiocb.aio_sigevent.sigev_notify = SIGEV_KEVENT;
    aio->aiocb.aio_sigevent.sigev_value.sival_ptr = ev;
#endif
    ev->handler = ngx_file_aio_event_handler;

    n = aio_read(&aio->aiocb);

    if (n == -1) {
        n = ngx_errno;

        if (n == NGX_EAGAIN) {
            return ngx_read_file(file, buf, size, offset);
        }

        ngx_log_error(NGX_LOG_CRIT, file->log, n,
                      "aio_read(\"%V\") failed", &file->name);

        if (n == NGX_ENOSYS) {
            ngx_file_aio = 0;
            return ngx_read_file(file, buf, size, offset);
        }

        return NGX_ERROR;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_CORE, file->log, 0,
                   "aio_read: fd:%d %d", file->fd, n);

    ev->active = 1;
    ev->ready = 0;
    ev->complete = 0;

    return ngx_file_aio_result(aio->file, aio, ev);
}