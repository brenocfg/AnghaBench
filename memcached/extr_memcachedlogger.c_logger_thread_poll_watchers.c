#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int failed_flush; int t; int /*<<< orphan*/  buf; int /*<<< orphan*/  sfd; scalar_t__ c; } ;
typedef  TYPE_1__ logger_watcher ;
struct TYPE_8__ {int (* read ) (scalar_t__,char*,int) ;int (* write ) (scalar_t__,unsigned char*,unsigned int) ;} ;
typedef  TYPE_2__ conn ;
struct TYPE_9__ {int events; int revents; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
#define  LOGGER_WATCHER_CLIENT 129 
#define  LOGGER_WATCHER_STDERR 128 
 int /*<<< orphan*/  L_DEBUG (char*,...) ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int WATCHER_ALL ; 
 int WATCHER_LIMIT ; 
 unsigned char* bipbuf_peek_all (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  bipbuf_poll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bipbuf_used (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fwrite (unsigned char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logger_thread_close_watcher (TYPE_1__*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (scalar_t__,char*,int) ; 
 int stub2 (scalar_t__,unsigned char*,unsigned int) ; 
 TYPE_1__** watchers ; 
 TYPE_3__* watchers_pollfds ; 

__attribute__((used)) static int logger_thread_poll_watchers(int force_poll, int watcher) {
    int x;
    int nfd = 0;
    unsigned char *data;
    unsigned int data_size = 0;
    int flushed = 0;

    for (x = 0; x < WATCHER_LIMIT; x++) {
        logger_watcher *w = watchers[x];
        if (w == NULL || (watcher != WATCHER_ALL && x != watcher))
            continue;

        data = bipbuf_peek_all(w->buf, &data_size);
        if (data != NULL) {
            watchers_pollfds[nfd].fd = w->sfd;
            watchers_pollfds[nfd].events = POLLOUT;
            nfd++;
        } else if (force_poll) {
            watchers_pollfds[nfd].fd = w->sfd;
            watchers_pollfds[nfd].events = POLLIN;
            nfd++;
        }
        /* This gets set after a call to poll, and should be used to gate on
         * calling poll again.
         */
        w->failed_flush = false;
    }

    if (nfd == 0)
        return 0;

    //L_DEBUG("LOGGER: calling poll() [data_size: %d]\n", data_size);
    int ret = poll(watchers_pollfds, nfd, 0);

    if (ret < 0) {
        perror("something failed with logger thread watcher fd polling");
        return -1;
    }

    nfd = 0;
    for (x = 0; x < WATCHER_LIMIT; x++) {
        logger_watcher *w = watchers[x];
        if (w == NULL)
            continue;

        data_size = 0;
        /* Early detection of a disconnect. Otherwise we have to wait until
         * the next write
         */
        if (watchers_pollfds[nfd].revents & POLLIN) {
            char buf[1];
            int res = ((conn*)w->c)->read(w->c, buf, 1);
            if (res == 0 || (res == -1 && (errno != EAGAIN && errno != EWOULDBLOCK))) {
                L_DEBUG("LOGGER: watcher closed remotely\n");
                logger_thread_close_watcher(w);
                nfd++;
                continue;
            }
        }
        if ((data = bipbuf_peek_all(w->buf, &data_size)) != NULL) {
            if (watchers_pollfds[nfd].revents & (POLLHUP|POLLERR)) {
                L_DEBUG("LOGGER: watcher closed during poll() call\n");
                logger_thread_close_watcher(w);
            } else if (watchers_pollfds[nfd].revents & POLLOUT) {
                int total = 0;

                /* We can write a bit. */
                switch (w->t) {
                    case LOGGER_WATCHER_STDERR:
                        total = fwrite(data, 1, data_size, stderr);
                        break;
                    case LOGGER_WATCHER_CLIENT:
                        total = ((conn*)w->c)->write(w->c, data, data_size);
                        break;
                }

                L_DEBUG("LOGGER: poll() wrote %d to %d (data_size: %d) (bipbuf_used: %d)\n", total, w->sfd,
                        data_size, bipbuf_used(w->buf));
                if (total == -1) {
                    if (errno != EAGAIN && errno != EWOULDBLOCK) {
                        logger_thread_close_watcher(w);
                    }
                    L_DEBUG("LOGGER: watcher hit EAGAIN\n");
                } else if (total == 0) {
                    logger_thread_close_watcher(w);
                } else {
                    bipbuf_poll(w->buf, total);
                    flushed += total;
                }
            }
        }
        nfd++;
    }
    return flushed;
}