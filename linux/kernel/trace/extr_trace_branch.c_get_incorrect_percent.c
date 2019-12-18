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
struct ftrace_branch_data {int correct; int incorrect; } ;

/* Variables and functions */

__attribute__((used)) static inline long get_incorrect_percent(struct ftrace_branch_data *p)
{
	long percent;

	if (p->correct) {
		percent = p->incorrect * 100;
		percent /= p->correct + p->incorrect;
	} else
		percent = p->incorrect ? 100 : -1;

	return percent;
}