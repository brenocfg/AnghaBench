#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct msghdr {scalar_t__ msg_iovlen; TYPE_3__* msg_iov; } ;
typedef  int ssize_t ;
typedef  enum transmit_result { ____Placeholder_transmit_result } transmit_result ;
struct TYPE_13__ {size_t msgcurr; size_t msgused; int (* sendmsg ) (TYPE_4__*,struct msghdr*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  transport; TYPE_2__* thread; struct msghdr* msglist; } ;
typedef  TYPE_4__ conn ;
typedef  scalar_t__ caddr_t ;
struct TYPE_14__ {scalar_t__ verbose; } ;
struct TYPE_12__ {int iov_len; scalar_t__ iov_base; } ;
struct TYPE_10__ {int bytes_written; int /*<<< orphan*/  mutex; } ;
struct TYPE_11__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int EV_PERSIST ; 
 int EV_WRITE ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ IS_UDP (int /*<<< orphan*/ ) ; 
 int TRANSMIT_COMPLETE ; 
 int TRANSMIT_HARD_ERROR ; 
 int TRANSMIT_INCOMPLETE ; 
 int TRANSMIT_SOFT_ERROR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_closing ; 
 int /*<<< orphan*/  conn_read ; 
 int /*<<< orphan*/  conn_set_state (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_8__ settings ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (TYPE_4__*,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_event (TYPE_4__*,int) ; 

__attribute__((used)) static enum transmit_result transmit(conn *c) {
    assert(c != NULL);

    if (c->msgcurr < c->msgused &&
            c->msglist[c->msgcurr].msg_iovlen == 0) {
        /* Finished writing the current msg; advance to the next. */
        c->msgcurr++;
    }
    if (c->msgcurr < c->msgused) {
        ssize_t res;
        struct msghdr *m = &c->msglist[c->msgcurr];

        res = c->sendmsg(c, m, 0);
        if (res >= 0) {
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.bytes_written += res;
            pthread_mutex_unlock(&c->thread->stats.mutex);

            /* We've written some of the data. Remove the completed
               iovec entries from the list of pending writes. */
            while (m->msg_iovlen > 0 && res >= m->msg_iov->iov_len) {
                res -= m->msg_iov->iov_len;
                m->msg_iovlen--;
                m->msg_iov++;
            }

            /* Might have written just part of the last iovec entry;
               adjust it so the next write will do the rest. */
            if (res > 0) {
                m->msg_iov->iov_base = (caddr_t)m->msg_iov->iov_base + res;
                m->msg_iov->iov_len -= res;
            }
            return TRANSMIT_INCOMPLETE;
        }
        if (res == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            if (!update_event(c, EV_WRITE | EV_PERSIST)) {
                if (settings.verbose > 0)
                    fprintf(stderr, "Couldn't update event\n");
                conn_set_state(c, conn_closing);
                return TRANSMIT_HARD_ERROR;
            }
            return TRANSMIT_SOFT_ERROR;
        }
        /* if res == -1 and error is not EAGAIN or EWOULDBLOCK,
           we have a real error, on which we close the connection */
        if (settings.verbose > 0)
            perror("Failed to write, and not due to blocking");

        if (IS_UDP(c->transport))
            conn_set_state(c, conn_read);
        else
            conn_set_state(c, conn_closing);
        return TRANSMIT_HARD_ERROR;
    } else {
        return TRANSMIT_COMPLETE;
    }
}