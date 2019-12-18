#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  timer ;
struct nn_msghdr {int msg_iovlen; void** msg_control; struct nn_iovec* msg_iov; void* msg_controllen; } ;
struct nn_iovec {void** iov_base; void* iov_len; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 void* NN_MSG ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memset (struct nn_msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 scalar_t__ nn_errno () ; 
 int /*<<< orphan*/  nn_freemsg (void*) ; 
 int nn_recvmsg (int,struct nn_msghdr*,int /*<<< orphan*/ ) ; 
 int nn_sendmsg (int,struct nn_msghdr*,int /*<<< orphan*/ ) ; 
 char* nn_strerror (scalar_t__) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void *worker (void *arg)
{
    int fd = (intptr_t)arg; 

    /*  Main processing loop. */

    for (;;) {
        uint32_t timer;
        int rc;
        int timeout;
        uint8_t *body;
        void *control;
        struct nn_iovec iov;
        struct nn_msghdr hdr;

        memset (&hdr, 0, sizeof (hdr));
        control = NULL;
        iov.iov_base = &body;
        iov.iov_len = NN_MSG;
        hdr.msg_iov = &iov;
        hdr.msg_iovlen = 1;
        hdr.msg_control = &control;
        hdr.msg_controllen = NN_MSG;

        rc = nn_recvmsg (fd, &hdr, 0);
        if (rc < 0) {
            if (nn_errno () == EBADF) {
                return (NULL);   /* Socket closed by another thread. */
            }
            /*  Any error here is unexpected. */
            fprintf (stderr, "nn_recv: %s\n", nn_strerror (nn_errno ()));
            break;
        }

        if (rc != sizeof (uint32_t)) {
            fprintf (stderr, "nn_recv: wanted %d, but got %d\n",
                (int) sizeof (uint32_t), rc);
            nn_freemsg (body);
            nn_freemsg (control);
            continue;
        }

        memcpy (&timer, body, sizeof (timer));
        nn_freemsg (body);

        /*  Poor mans usleep but in msec. */
        poll (NULL, 0, ntohl (timer));

        hdr.msg_iov = NULL;
        hdr.msg_iovlen = 0;

        rc = nn_sendmsg (fd, &hdr, 0);
        if (rc < 0) {
            fprintf (stderr, "nn_send: %s\n", nn_strerror (nn_errno ()));
            nn_freemsg (control);
        }
    }

    /*  We got here, so close the file.  That will cause the other threads
        to shut down too. */

    nn_close (fd);
    return (NULL);
}