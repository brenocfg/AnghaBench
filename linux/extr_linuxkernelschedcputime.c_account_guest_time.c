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
typedef  scalar_t__ u64 ;
struct task_struct {int /*<<< orphan*/  gtime; int /*<<< orphan*/  utime; } ;
struct TYPE_2__ {scalar_t__* cpustat; } ;

/* Variables and functions */
 size_t CPUTIME_GUEST ; 
 size_t CPUTIME_GUEST_NICE ; 
 size_t CPUTIME_NICE ; 
 size_t CPUTIME_USER ; 
 int /*<<< orphan*/  account_group_user_time (struct task_struct*,scalar_t__) ; 
 TYPE_1__* kcpustat_this_cpu ; 
 scalar_t__ task_nice (struct task_struct*) ; 

void account_guest_time(struct task_struct *p, u64 cputime)
{
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	/* Add guest time to process. */
	p->utime += cputime;
	account_group_user_time(p, cputime);
	p->gtime += cputime;

	/* Add guest time to cpustat. */
	if (task_nice(p) > 0) {
		cpustat[CPUTIME_NICE] += cputime;
		cpustat[CPUTIME_GUEST_NICE] += cputime;
	} else {
		cpustat[CPUTIME_USER] += cputime;
		cpustat[CPUTIME_GUEST] += cputime;
	}
}