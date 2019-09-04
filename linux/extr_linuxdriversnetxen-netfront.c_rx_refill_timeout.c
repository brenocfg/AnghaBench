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
struct timer_list {int dummy; } ;
struct netfront_queue {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 struct netfront_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct netfront_queue* queue ; 
 int /*<<< orphan*/  rx_refill_timer ; 

__attribute__((used)) static void rx_refill_timeout(struct timer_list *t)
{
	struct netfront_queue *queue = from_timer(queue, t, rx_refill_timer);
	napi_schedule(&queue->napi);
}