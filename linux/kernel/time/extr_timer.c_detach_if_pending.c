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
struct timer_list {int /*<<< orphan*/  entry; } ;
struct timer_base {int /*<<< orphan*/  pending_map; scalar_t__ vectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_timer (struct timer_list*,int) ; 
 scalar_t__ hlist_is_singular_node (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int timer_get_idx (struct timer_list*) ; 
 int /*<<< orphan*/  timer_pending (struct timer_list*) ; 

__attribute__((used)) static int detach_if_pending(struct timer_list *timer, struct timer_base *base,
			     bool clear_pending)
{
	unsigned idx = timer_get_idx(timer);

	if (!timer_pending(timer))
		return 0;

	if (hlist_is_singular_node(&timer->entry, base->vectors + idx))
		__clear_bit(idx, base->pending_map);

	detach_timer(timer, clear_pending);
	return 1;
}