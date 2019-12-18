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
typedef  int u64 ;
struct TYPE_3__ {int* pmc_count; int ebb_count; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 size_t PMC_INDEX (int) ; 
 TYPE_2__ ebb_state ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,...) ; 

bool ebb_check_count(int pmc, u64 sample_period, int fudge)
{
	u64 count, upper, lower;

	count = ebb_state.stats.pmc_count[PMC_INDEX(pmc)];

	lower = ebb_state.stats.ebb_count * (sample_period - fudge);

	if (count < lower) {
		printf("PMC%d count (0x%llx) below lower limit 0x%llx (-0x%llx)\n",
			pmc, count, lower, lower - count);
		return false;
	}

	upper = ebb_state.stats.ebb_count * (sample_period + fudge);

	if (count > upper) {
		printf("PMC%d count (0x%llx) above upper limit 0x%llx (+0x%llx)\n",
			pmc, count, upper, count - upper);
		return false;
	}

	printf("PMC%d count (0x%llx) is between 0x%llx and 0x%llx delta +0x%llx/-0x%llx\n",
		pmc, count, lower, upper, count - lower, upper - count);

	return true;
}