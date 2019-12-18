#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout_fd ;
struct TYPE_8__ {TYPE_2__* thread; int /*<<< orphan*/  ssl_wbuf; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ conn ;
struct TYPE_11__ {scalar_t__ verbose; int /*<<< orphan*/  ssl_enabled; } ;
struct TYPE_10__ {int sfd; int /*<<< orphan*/  c; int /*<<< orphan*/  ssl; int /*<<< orphan*/  transport; int /*<<< orphan*/  read_buffer_size; int /*<<< orphan*/  event_flags; int /*<<< orphan*/  init_state; int /*<<< orphan*/  mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  base; int /*<<< orphan*/  ssl_wbuf; int /*<<< orphan*/  new_conn_queue; } ;
typedef  TYPE_2__ LIBEVENT_THREAD ;
typedef  TYPE_3__ CQ_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  conn_close_idle (int /*<<< orphan*/ ) ; 
 TYPE_1__* conn_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_worker_readd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * conns ; 
 TYPE_3__* cq_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqi_free (TYPE_3__*) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
#define  queue_new_conn 129 
#define  queue_redispatch 128 
 int read (int,...) ; 
 int /*<<< orphan*/  register_thread_initialized () ; 
 TYPE_4__ settings ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void thread_libevent_process(int fd, short which, void *arg) {
    LIBEVENT_THREAD *me = arg;
    CQ_ITEM *item;
    char buf[1];
    conn *c;
    unsigned int timeout_fd;

    if (read(fd, buf, 1) != 1) {
        if (settings.verbose > 0)
            fprintf(stderr, "Can't read from libevent pipe\n");
        return;
    }

    switch (buf[0]) {
    case 'c':
        item = cq_pop(me->new_conn_queue);

        if (NULL == item) {
            break;
        }
        switch (item->mode) {
            case queue_new_conn:
                c = conn_new(item->sfd, item->init_state, item->event_flags,
                                   item->read_buffer_size, item->transport,
                                   me->base, item->ssl);
                if (c == NULL) {
                    if (IS_UDP(item->transport)) {
                        fprintf(stderr, "Can't listen for events on UDP socket\n");
                        exit(1);
                    } else {
                        if (settings.verbose > 0) {
                            fprintf(stderr, "Can't listen for events on fd %d\n",
                                item->sfd);
                        }
#ifdef TLS
                        if (item->ssl) {
                            SSL_shutdown(item->ssl);
                            SSL_free(item->ssl);
                        }
#endif
                        close(item->sfd);
                    }
                } else {
                    c->thread = me;
#ifdef TLS
                    if (settings.ssl_enabled && c->ssl != NULL) {
                        assert(c->thread && c->thread->ssl_wbuf);
                        c->ssl_wbuf = c->thread->ssl_wbuf;
                    }
#endif
                }
                break;

            case queue_redispatch:
                conn_worker_readd(item->c);
                break;
        }
        cqi_free(item);
        break;
    /* we were told to pause and report in */
    case 'p':
        register_thread_initialized();
        break;
    /* a client socket timed out */
    case 't':
        if (read(fd, &timeout_fd, sizeof(timeout_fd)) != sizeof(timeout_fd)) {
            if (settings.verbose > 0)
                fprintf(stderr, "Can't read timeout fd from libevent pipe\n");
            return;
        }
        conn_close_idle(conns[timeout_fd]);
        break;
    /* asked to stop */
    case 's':
        event_base_loopexit(me->base, NULL);
        break;
    }
}