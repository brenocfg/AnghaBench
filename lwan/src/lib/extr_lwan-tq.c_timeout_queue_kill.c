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
struct timeout_queue {int /*<<< orphan*/  lwan; } ;
struct lwan_connection {int /*<<< orphan*/ * coro; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coro_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_connection_get_fd (int /*<<< orphan*/ ,struct lwan_connection*) ; 
 int /*<<< orphan*/  timeout_queue_remove (struct timeout_queue*,struct lwan_connection*) ; 

void timeout_queue_kill(struct timeout_queue *tq, struct lwan_connection *conn)
{
    timeout_queue_remove(tq, conn);

    if (LIKELY(conn->coro)) {
        coro_free(conn->coro);
        conn->coro = NULL;

        close(lwan_connection_get_fd(tq->lwan, conn));
    }
}