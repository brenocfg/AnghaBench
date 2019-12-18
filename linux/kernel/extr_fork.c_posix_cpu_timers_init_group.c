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
struct posix_cputimers {int dummy; } ;
struct signal_struct {TYPE_1__* rlim; struct posix_cputimers posix_cputimers; } ;
struct TYPE_2__ {int /*<<< orphan*/  rlim_cur; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t RLIMIT_CPU ; 
 int /*<<< orphan*/  posix_cputimers_group_init (struct posix_cputimers*,unsigned long) ; 

__attribute__((used)) static void posix_cpu_timers_init_group(struct signal_struct *sig)
{
	struct posix_cputimers *pct = &sig->posix_cputimers;
	unsigned long cpu_limit;

	cpu_limit = READ_ONCE(sig->rlim[RLIMIT_CPU].rlim_cur);
	posix_cputimers_group_init(pct, cpu_limit);
}