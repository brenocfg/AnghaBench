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
struct timer_base {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int __collect_expired_timers (struct timer_base*,struct hlist_head*) ; 

__attribute__((used)) static inline int collect_expired_timers(struct timer_base *base,
					 struct hlist_head *heads)
{
	return __collect_expired_timers(base, heads);
}