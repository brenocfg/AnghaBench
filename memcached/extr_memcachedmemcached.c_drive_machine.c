#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_31__ {int it_flags; } ;
typedef  TYPE_3__ item ;
struct TYPE_32__ {int state; int rbytes; int rlbytes; int ritem; int rcurr; int (* read ) (TYPE_4__*,int,int) ;int sbytes; int write_and_go; int rbuf; int rsize; int iovused; int /*<<< orphan*/  transport; int /*<<< orphan*/  write_and_free; int /*<<< orphan*/  protocol; int /*<<< orphan*/  msgcurr; int /*<<< orphan*/  wbytes; int /*<<< orphan*/  wcurr; TYPE_2__* thread; scalar_t__ item; int /*<<< orphan*/  sfd; } ;
typedef  TYPE_4__ conn ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_29__ {int bytes_read; int /*<<< orphan*/  mutex; int /*<<< orphan*/  conn_yields; } ;
struct TYPE_30__ {TYPE_1__ stats; } ;
struct TYPE_28__ {int reqs_per_event; int /*<<< orphan*/  verbose; int /*<<< orphan*/  maxconns; int /*<<< orphan*/  maxconns_fast; } ;
struct TYPE_27__ {int /*<<< orphan*/  rejected_conns; } ;
struct TYPE_26__ {scalar_t__ reserved_fds; scalar_t__ curr_conns; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_BUFFER_SIZE ; 
 int EAGAIN ; 
 int EMFILE ; 
 int ENOSYS ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IS_UDP (int /*<<< orphan*/ ) ; 
 int ITEM_CHUNKED ; 
 int O_NONBLOCK ; 
#define  READ_DATA_RECEIVED 148 
#define  READ_ERROR 147 
#define  READ_MEMORY_ERROR 146 
#define  READ_NO_DATA_RECEIVED 145 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
#define  TRANSMIT_COMPLETE 144 
#define  TRANSMIT_HARD_ERROR 143 
#define  TRANSMIT_INCOMPLETE 142 
#define  TRANSMIT_SOFT_ERROR 141 
 int /*<<< orphan*/  abort () ; 
 int accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  accept_new_conns (int) ; 
 int /*<<< orphan*/  add_iov (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binary_prot ; 
 int /*<<< orphan*/  build_udp_headers (TYPE_4__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  complete_nread (TYPE_4__*) ; 
 int /*<<< orphan*/  conn_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  conn_close (TYPE_4__*) ; 
#define  conn_closed 140 
#define  conn_closing 139 
#define  conn_listening 138 
#define  conn_max_state 137 
#define  conn_mwrite 136 
#define  conn_new_cmd 135 
#define  conn_nread 134 
#define  conn_parse_cmd 133 
#define  conn_read 132 
 int /*<<< orphan*/  conn_release_items (TYPE_4__*) ; 
 int /*<<< orphan*/  conn_set_state (TYPE_4__*,int const) ; 
#define  conn_swallow 131 
#define  conn_waiting 130 
#define  conn_watch 129 
#define  conn_write 128 
 int /*<<< orphan*/  dispatch_conn_new (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_into_chunked_item (TYPE_4__*) ; 
 int /*<<< orphan*/  reset_cmd_handler (TYPE_4__*) ; 
 TYPE_14__ settings ; 
 TYPE_13__ stats ; 
 TYPE_12__ stats_state ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int stub1 (TYPE_4__*,int,int) ; 
 int stub2 (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  transmit (TYPE_4__*) ; 
 int /*<<< orphan*/  try_read_command (TYPE_4__*) ; 
 int try_read_network (TYPE_4__*) ; 
 int try_read_udp (TYPE_4__*) ; 
 int /*<<< orphan*/  update_event (TYPE_4__*,int) ; 
 int write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drive_machine(conn *c) {
    bool stop = false;
    int sfd;
    socklen_t addrlen;
    struct sockaddr_storage addr;
    int nreqs = settings.reqs_per_event;
    int res;
    const char *str;
#ifdef HAVE_ACCEPT4
    static int  use_accept4 = 1;
#else
    static int  use_accept4 = 0;
#endif

    assert(c != NULL);

    while (!stop) {

        switch(c->state) {
        case conn_listening:
            addrlen = sizeof(addr);
#ifdef HAVE_ACCEPT4
            if (use_accept4) {
                sfd = accept4(c->sfd, (struct sockaddr *)&addr, &addrlen, SOCK_NONBLOCK);
            } else {
                sfd = accept(c->sfd, (struct sockaddr *)&addr, &addrlen);
            }
#else
            sfd = accept(c->sfd, (struct sockaddr *)&addr, &addrlen);
#endif
            if (sfd == -1) {
                if (use_accept4 && errno == ENOSYS) {
                    use_accept4 = 0;
                    continue;
                }
                perror(use_accept4 ? "accept4()" : "accept()");
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    /* these are transient, so don't log anything */
                    stop = true;
                } else if (errno == EMFILE) {
                    if (settings.verbose > 0)
                        fprintf(stderr, "Too many open connections\n");
                    accept_new_conns(false);
                    stop = true;
                } else {
                    perror("accept()");
                    stop = true;
                }
                break;
            }
            if (!use_accept4) {
                if (fcntl(sfd, F_SETFL, fcntl(sfd, F_GETFL) | O_NONBLOCK) < 0) {
                    perror("setting O_NONBLOCK");
                    close(sfd);
                    break;
                }
            }

            if (settings.maxconns_fast &&
                stats_state.curr_conns + stats_state.reserved_fds >= settings.maxconns - 1) {
                str = "ERROR Too many open connections\r\n";
                res = write(sfd, str, strlen(str));
                close(sfd);
                STATS_LOCK();
                stats.rejected_conns++;
                STATS_UNLOCK();
            } else {
                void *ssl_v = NULL;
#ifdef TLS
                SSL *ssl = NULL;
                if (c->ssl_enabled) {
                    assert(IS_TCP(c->transport) && settings.ssl_enabled);

                    if (settings.ssl_ctx == NULL) {
                        if (settings.verbose) {
                            fprintf(stderr, "SSL context is not initialized\n");
                        }
                        close(sfd);
                        break;
                    }
                    SSL_LOCK();
                    ssl = SSL_new(settings.ssl_ctx);
                    SSL_UNLOCK();
                    if (ssl == NULL) {
                        if (settings.verbose) {
                            fprintf(stderr, "Failed to created the SSL object\n");
                        }
                        close(sfd);
                        break;
                    }
                    SSL_set_fd(ssl, sfd);
                    int ret = SSL_accept(ssl);
                    if (ret < 0) {
                        int err = SSL_get_error(ssl, ret);
                        if (err == SSL_ERROR_SYSCALL || err == SSL_ERROR_SSL) {
                            if (settings.verbose) {
                                fprintf(stderr, "SSL connection failed with error code : %d : %s\n", err, strerror(errno));
                            }
                            close(sfd);
                            break;
                        }
                    }
                }
                ssl_v = (void*) ssl;
#endif

                dispatch_conn_new(sfd, conn_new_cmd, EV_READ | EV_PERSIST,
                                     DATA_BUFFER_SIZE, c->transport, ssl_v);
            }

            stop = true;
            break;

        case conn_waiting:
            if (!update_event(c, EV_READ | EV_PERSIST)) {
                if (settings.verbose > 0)
                    fprintf(stderr, "Couldn't update event\n");
                conn_set_state(c, conn_closing);
                break;
            }

            conn_set_state(c, conn_read);
            stop = true;
            break;

        case conn_read:
            res = IS_UDP(c->transport) ? try_read_udp(c) : try_read_network(c);

            switch (res) {
            case READ_NO_DATA_RECEIVED:
                conn_set_state(c, conn_waiting);
                break;
            case READ_DATA_RECEIVED:
                conn_set_state(c, conn_parse_cmd);
                break;
            case READ_ERROR:
                conn_set_state(c, conn_closing);
                break;
            case READ_MEMORY_ERROR: /* Failed to allocate more memory */
                /* State already set by try_read_network */
                break;
            }
            break;

        case conn_parse_cmd :
            if (try_read_command(c) == 0) {
                /* wee need more data! */
                conn_set_state(c, conn_waiting);
            }

            break;

        case conn_new_cmd:
            /* Only process nreqs at a time to avoid starving other
               connections */

            --nreqs;
            if (nreqs >= 0) {
                reset_cmd_handler(c);
            } else {
                pthread_mutex_lock(&c->thread->stats.mutex);
                c->thread->stats.conn_yields++;
                pthread_mutex_unlock(&c->thread->stats.mutex);
                if (c->rbytes > 0) {
                    /* We have already read in data into the input buffer,
                       so libevent will most likely not signal read events
                       on the socket (unless more data is available. As a
                       hack we should just put in a request to write data,
                       because that should be possible ;-)
                    */
                    if (!update_event(c, EV_WRITE | EV_PERSIST)) {
                        if (settings.verbose > 0)
                            fprintf(stderr, "Couldn't update event\n");
                        conn_set_state(c, conn_closing);
                        break;
                    }
                }
                stop = true;
            }
            break;

        case conn_nread:
            if (c->rlbytes == 0) {
                complete_nread(c);
                break;
            }

            /* Check if rbytes < 0, to prevent crash */
            if (c->rlbytes < 0) {
                if (settings.verbose) {
                    fprintf(stderr, "Invalid rlbytes to read: len %d\n", c->rlbytes);
                }
                conn_set_state(c, conn_closing);
                break;
            }

            if (!c->item || (((item *)c->item)->it_flags & ITEM_CHUNKED) == 0) {
                /* first check if we have leftovers in the conn_read buffer */
                if (c->rbytes > 0) {
                    int tocopy = c->rbytes > c->rlbytes ? c->rlbytes : c->rbytes;
                    if (c->ritem != c->rcurr) {
                        memmove(c->ritem, c->rcurr, tocopy);
                    }
                    c->ritem += tocopy;
                    c->rlbytes -= tocopy;
                    c->rcurr += tocopy;
                    c->rbytes -= tocopy;
                    if (c->rlbytes == 0) {
                        break;
                    }
                }

                /*  now try reading from the socket */
                res = c->read(c, c->ritem, c->rlbytes);
                if (res > 0) {
                    pthread_mutex_lock(&c->thread->stats.mutex);
                    c->thread->stats.bytes_read += res;
                    pthread_mutex_unlock(&c->thread->stats.mutex);
                    if (c->rcurr == c->ritem) {
                        c->rcurr += res;
                    }
                    c->ritem += res;
                    c->rlbytes -= res;
                    break;
                }
            } else {
                res = read_into_chunked_item(c);
                if (res > 0)
                    break;
            }

            if (res == 0) { /* end of stream */
                conn_set_state(c, conn_closing);
                break;
            }

            if (res == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                if (!update_event(c, EV_READ | EV_PERSIST)) {
                    if (settings.verbose > 0)
                        fprintf(stderr, "Couldn't update event\n");
                    conn_set_state(c, conn_closing);
                    break;
                }
                stop = true;
                break;
            }

            /* Memory allocation failure */
            if (res == -2) {
                out_of_memory(c, "SERVER_ERROR Out of memory during read");
                c->sbytes = c->rlbytes;
                c->write_and_go = conn_swallow;
                break;
            }
            /* otherwise we have a real error, on which we close the connection */
            if (settings.verbose > 0) {
                fprintf(stderr, "Failed to read, and not due to blocking:\n"
                        "errno: %d %s \n"
                        "rcurr=%lx ritem=%lx rbuf=%lx rlbytes=%d rsize=%d\n",
                        errno, strerror(errno),
                        (long)c->rcurr, (long)c->ritem, (long)c->rbuf,
                        (int)c->rlbytes, (int)c->rsize);
            }
            conn_set_state(c, conn_closing);
            break;

        case conn_swallow:
            /* we are reading sbytes and throwing them away */
            if (c->sbytes <= 0) {
                conn_set_state(c, conn_new_cmd);
                break;
            }

            /* first check if we have leftovers in the conn_read buffer */
            if (c->rbytes > 0) {
                int tocopy = c->rbytes > c->sbytes ? c->sbytes : c->rbytes;
                c->sbytes -= tocopy;
                c->rcurr += tocopy;
                c->rbytes -= tocopy;
                break;
            }

            /*  now try reading from the socket */
            res = c->read(c, c->rbuf, c->rsize > c->sbytes ? c->sbytes : c->rsize);
            if (res > 0) {
                pthread_mutex_lock(&c->thread->stats.mutex);
                c->thread->stats.bytes_read += res;
                pthread_mutex_unlock(&c->thread->stats.mutex);
                c->sbytes -= res;
                break;
            }
            if (res == 0) { /* end of stream */
                conn_set_state(c, conn_closing);
                break;
            }
            if (res == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                if (!update_event(c, EV_READ | EV_PERSIST)) {
                    if (settings.verbose > 0)
                        fprintf(stderr, "Couldn't update event\n");
                    conn_set_state(c, conn_closing);
                    break;
                }
                stop = true;
                break;
            }
            /* otherwise we have a real error, on which we close the connection */
            if (settings.verbose > 0)
                fprintf(stderr, "Failed to read, and not due to blocking\n");
            conn_set_state(c, conn_closing);
            break;

        case conn_write:
            /*
             * We want to write out a simple response. If we haven't already,
             * assemble it into a msgbuf list (this will be a single-entry
             * list for TCP or a two-entry list for UDP).
             */
            if (c->iovused == 0 || (IS_UDP(c->transport) && c->iovused == 1)) {
                if (add_iov(c, c->wcurr, c->wbytes) != 0) {
                    if (settings.verbose > 0)
                        fprintf(stderr, "Couldn't build response\n");
                    conn_set_state(c, conn_closing);
                    break;
                }
            }

            /* fall through... */

        case conn_mwrite:
#ifdef EXTSTORE
            /* have side IO's that must process before transmit() can run.
             * remove the connection from the worker thread and dispatch the
             * IO queue
             */
            if (c->io_wrapleft) {
                assert(c->io_queued == false);
                assert(c->io_wraplist != NULL);
                // TODO: create proper state for this condition
                conn_set_state(c, conn_watch);
                event_del(&c->event);
                c->io_queued = true;
                extstore_submit(c->thread->storage, &c->io_wraplist->io);
                stop = true;
                break;
            }
#endif
          if (IS_UDP(c->transport) && c->msgcurr == 0 && build_udp_headers(c) != 0) {
            if (settings.verbose > 0)
              fprintf(stderr, "Failed to build UDP headers\n");
            conn_set_state(c, conn_closing);
            break;
          }
            switch (transmit(c)) {
            case TRANSMIT_COMPLETE:
                if (c->state == conn_mwrite) {
                    conn_release_items(c);
                    /* XXX:  I don't know why this wasn't the general case */
                    if(c->protocol == binary_prot) {
                        conn_set_state(c, c->write_and_go);
                    } else {
                        conn_set_state(c, conn_new_cmd);
                    }
                } else if (c->state == conn_write) {
                    if (c->write_and_free) {
                        free(c->write_and_free);
                        c->write_and_free = 0;
                    }
                    conn_set_state(c, c->write_and_go);
                } else {
                    if (settings.verbose > 0)
                        fprintf(stderr, "Unexpected state %d\n", c->state);
                    conn_set_state(c, conn_closing);
                }
                break;

            case TRANSMIT_INCOMPLETE:
            case TRANSMIT_HARD_ERROR:
                break;                   /* Continue in state machine. */

            case TRANSMIT_SOFT_ERROR:
                stop = true;
                break;
            }
            break;

        case conn_closing:
            if (IS_UDP(c->transport))
                conn_cleanup(c);
            else
                conn_close(c);
            stop = true;
            break;

        case conn_closed:
            /* This only happens if dormando is an idiot. */
            abort();
            break;

        case conn_watch:
            /* We handed off our connection to the logger thread. */
            stop = true;
            break;
        case conn_max_state:
            assert(false);
            break;
        }
    }

    return;
}