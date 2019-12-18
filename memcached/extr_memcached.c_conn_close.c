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
struct TYPE_7__ {int sfd; scalar_t__ ssl; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ conn ;
struct TYPE_9__ {int verbose; } ;
struct TYPE_8__ {int /*<<< orphan*/  curr_conns; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCACHED_CONN_RELEASE (int) ; 
 int /*<<< orphan*/  SSL_free (scalar_t__) ; 
 int /*<<< orphan*/  SSL_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int allow_new_conns ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  conn_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  conn_closed ; 
 int /*<<< orphan*/  conn_lock ; 
 int /*<<< orphan*/  conn_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ settings ; 
 TYPE_2__ stats_state ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void conn_close(conn *c) {
    assert(c != NULL);

    /* delete the event, the socket and the conn */
    event_del(&c->event);

    if (settings.verbose > 1)
        fprintf(stderr, "<%d connection closed.\n", c->sfd);

    conn_cleanup(c);

    MEMCACHED_CONN_RELEASE(c->sfd);
    conn_set_state(c, conn_closed);
#ifdef TLS
    if (c->ssl) {
        SSL_shutdown(c->ssl);
        SSL_free(c->ssl);
    }
#endif
    close(c->sfd);
    pthread_mutex_lock(&conn_lock);
    allow_new_conns = true;
    pthread_mutex_unlock(&conn_lock);

    STATS_LOCK();
    stats_state.curr_conns--;
    STATS_UNLOCK();

    return;
}