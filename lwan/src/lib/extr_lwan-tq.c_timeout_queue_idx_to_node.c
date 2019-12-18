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

/* Variables and functions */

__attribute__((used)) static inline struct lwan_connection *
timeout_queue_idx_to_node(struct timeout_queue *tq, int idx)
{
    return (idx < 0) ? &tq->head : &tq->conns[idx];
}