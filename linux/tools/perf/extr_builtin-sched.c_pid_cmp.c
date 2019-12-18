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
struct work_atoms {TYPE_1__* thread; } ;
struct TYPE_2__ {scalar_t__ tid; } ;

/* Variables and functions */

__attribute__((used)) static int pid_cmp(struct work_atoms *l, struct work_atoms *r)
{
	if (l->thread == r->thread)
		return 0;
	if (l->thread->tid < r->thread->tid)
		return -1;
	if (l->thread->tid > r->thread->tid)
		return 1;
	return (int)(l->thread - r->thread);
}