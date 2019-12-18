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
struct timer_list {int /*<<< orphan*/  flags; int /*<<< orphan*/  expires; int /*<<< orphan*/  entry; } ;
struct timer_base {int /*<<< orphan*/  pending_map; scalar_t__ vectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_set_idx (struct timer_list*,unsigned int) ; 
 int /*<<< orphan*/  trace_timer_start (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enqueue_timer(struct timer_base *base, struct timer_list *timer,
			  unsigned int idx)
{
	hlist_add_head(&timer->entry, base->vectors + idx);
	__set_bit(idx, base->pending_map);
	timer_set_idx(timer, idx);

	trace_timer_start(timer, timer->expires, timer->flags);
}