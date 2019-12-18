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
typedef  int u64 ;
struct posix_cputimers {int timers_active; TYPE_1__* bases; } ;
struct TYPE_2__ {int nextevt; } ;

/* Variables and functions */
 size_t CPUCLOCK_PROF ; 
 int NSEC_PER_SEC ; 
 int RLIM_INFINITY ; 
 int /*<<< orphan*/  posix_cputimers_init (struct posix_cputimers*) ; 

void posix_cputimers_group_init(struct posix_cputimers *pct, u64 cpu_limit)
{
	posix_cputimers_init(pct);
	if (cpu_limit != RLIM_INFINITY) {
		pct->bases[CPUCLOCK_PROF].nextevt = cpu_limit * NSEC_PER_SEC;
		pct->timers_active = true;
	}
}