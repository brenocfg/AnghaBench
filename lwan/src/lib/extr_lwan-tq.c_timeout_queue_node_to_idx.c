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
struct lwan_connection {int dummy; } ;
struct timeout_queue {struct lwan_connection* conns; struct lwan_connection head; } ;
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static inline int timeout_queue_node_to_idx(struct timeout_queue *tq,
                                            struct lwan_connection *conn)
{
    return (conn == &tq->head) ? -1 : (int)(ptrdiff_t)(conn - tq->conns);
}