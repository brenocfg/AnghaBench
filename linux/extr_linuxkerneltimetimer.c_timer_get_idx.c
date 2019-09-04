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
struct timer_list {unsigned int flags; } ;

/* Variables and functions */
 unsigned int TIMER_ARRAYMASK ; 
 unsigned int TIMER_ARRAYSHIFT ; 

__attribute__((used)) static inline unsigned int timer_get_idx(struct timer_list *timer)
{
	return (timer->flags & TIMER_ARRAYMASK) >> TIMER_ARRAYSHIFT;
}