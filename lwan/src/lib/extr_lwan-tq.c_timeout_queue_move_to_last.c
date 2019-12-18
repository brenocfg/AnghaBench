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
struct timeout_queue {scalar_t__ keep_alive_timeout; scalar_t__ time; } ;
struct lwan_connection {scalar_t__ time_to_die; } ;

/* Variables and functions */
 int /*<<< orphan*/  timeout_queue_insert (struct timeout_queue*,struct lwan_connection*) ; 
 int /*<<< orphan*/  timeout_queue_remove (struct timeout_queue*,struct lwan_connection*) ; 

void timeout_queue_move_to_last(struct timeout_queue *tq,
                                struct lwan_connection *conn)
{
    /* CONN_IS_KEEP_ALIVE isn't checked here because non-keep-alive connections
     * are closed in the request processing coroutine after they have been
     * served.  In practice, if this is called, it's a keep-alive connection. */
    conn->time_to_die = tq->time + tq->keep_alive_timeout;

    timeout_queue_remove(tq, conn);
    timeout_queue_insert(tq, conn);
}