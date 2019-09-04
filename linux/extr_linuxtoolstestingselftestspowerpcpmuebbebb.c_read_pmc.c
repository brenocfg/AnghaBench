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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int /*<<< orphan*/  SPRN_PMC2 ; 
 int /*<<< orphan*/  SPRN_PMC3 ; 
 int /*<<< orphan*/  SPRN_PMC4 ; 
 int /*<<< orphan*/  SPRN_PMC5 ; 
 int /*<<< orphan*/  SPRN_PMC6 ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 

u64 read_pmc(int pmc)
{
	switch (pmc) {
		case 1: return mfspr(SPRN_PMC1);
		case 2: return mfspr(SPRN_PMC2);
		case 3: return mfspr(SPRN_PMC3);
		case 4: return mfspr(SPRN_PMC4);
		case 5: return mfspr(SPRN_PMC5);
		case 6: return mfspr(SPRN_PMC6);
	}

	return 0;
}