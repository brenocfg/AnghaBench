#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ebb_count; int spurious; int negative; int no_overflow; int /*<<< orphan*/ * pmc_count; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 TYPE_2__ ebb_state ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dump_summary_ebb_state(void)
{
	printf("ebb_state:\n"			\
	       "  ebb_count    = %d\n"		\
	       "  spurious     = %d\n"		\
	       "  negative     = %d\n"		\
	       "  no_overflow  = %d\n"		\
	       "  pmc[1] count = 0x%llx\n"	\
	       "  pmc[2] count = 0x%llx\n"	\
	       "  pmc[3] count = 0x%llx\n"	\
	       "  pmc[4] count = 0x%llx\n"	\
	       "  pmc[5] count = 0x%llx\n"	\
	       "  pmc[6] count = 0x%llx\n",
		ebb_state.stats.ebb_count, ebb_state.stats.spurious,
		ebb_state.stats.negative, ebb_state.stats.no_overflow,
		ebb_state.stats.pmc_count[0], ebb_state.stats.pmc_count[1],
		ebb_state.stats.pmc_count[2], ebb_state.stats.pmc_count[3],
		ebb_state.stats.pmc_count[4], ebb_state.stats.pmc_count[5]);
}