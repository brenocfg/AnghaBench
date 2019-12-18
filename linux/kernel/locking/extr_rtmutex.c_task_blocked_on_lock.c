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
struct task_struct {TYPE_1__* pi_blocked_on; } ;
struct rt_mutex {int dummy; } ;
struct TYPE_2__ {struct rt_mutex* lock; } ;

/* Variables and functions */

__attribute__((used)) static inline struct rt_mutex *task_blocked_on_lock(struct task_struct *p)
{
	return p->pi_blocked_on ? p->pi_blocked_on->lock : NULL;
}