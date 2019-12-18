#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct timeout_queue {scalar_t__ time; TYPE_1__ head; } ;
struct lwan_connection {scalar_t__ time_to_die; } ;

/* Variables and functions */
 int /*<<< orphan*/  timeout_queue_empty (struct timeout_queue*) ; 
 struct lwan_connection* timeout_queue_idx_to_node (struct timeout_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_queue_kill (struct timeout_queue*,struct lwan_connection*) ; 

void timeout_queue_kill_waiting(struct timeout_queue *tq)
{
    tq->time++;

    while (!timeout_queue_empty(tq)) {
        struct lwan_connection *conn =
            timeout_queue_idx_to_node(tq, tq->head.next);

        if (conn->time_to_die > tq->time)
            return;

        timeout_queue_kill(tq, conn);
    }

    /* Death queue exhausted: reset epoch */
    tq->time = 0;
}