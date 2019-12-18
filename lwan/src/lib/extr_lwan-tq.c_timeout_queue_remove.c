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
struct timeout_queue {int dummy; } ;
struct lwan_connection {int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 struct lwan_connection* timeout_queue_idx_to_node (struct timeout_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timeout_queue_remove(struct timeout_queue *tq,
                                 struct lwan_connection *node)
{
    struct lwan_connection *prev = timeout_queue_idx_to_node(tq, node->prev);
    struct lwan_connection *next = timeout_queue_idx_to_node(tq, node->next);

    next->prev = node->prev;
    prev->next = node->next;

    node->next = node->prev = -1;
}