#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t sfd; int /*<<< orphan*/ * ssl_wbuf; struct TYPE_5__* iov; struct TYPE_5__* suffixlist; struct TYPE_5__* ilist; struct TYPE_5__* wbuf; struct TYPE_5__* rbuf; struct TYPE_5__* msglist; struct TYPE_5__* hdrbuf; } ;
typedef  TYPE_1__ conn ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCACHED_CONN_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** conns ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 size_t max_fds ; 

void conn_free(conn *c) {
    if (c) {
        assert(c != NULL);
        assert(c->sfd >= 0 && c->sfd < max_fds);

        MEMCACHED_CONN_DESTROY(c);
        conns[c->sfd] = NULL;
        if (c->hdrbuf)
            free(c->hdrbuf);
        if (c->msglist)
            free(c->msglist);
        if (c->rbuf)
            free(c->rbuf);
        if (c->wbuf)
            free(c->wbuf);
        if (c->ilist)
            free(c->ilist);
        if (c->suffixlist)
            free(c->suffixlist);
        if (c->iov)
            free(c->iov);
#ifdef TLS
        if (c->ssl_wbuf)
            c->ssl_wbuf = NULL;
#endif

        free(c);
    }
}