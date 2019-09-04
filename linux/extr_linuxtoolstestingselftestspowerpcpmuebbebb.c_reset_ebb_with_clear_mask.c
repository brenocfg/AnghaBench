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
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long BESCR_PME ; 
 unsigned long BESCR_PMEO ; 
 unsigned long MMCR0_PMAE ; 
 int /*<<< orphan*/  SPRN_BESCRR ; 
 int /*<<< orphan*/  SPRN_BESCRS ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 

void reset_ebb_with_clear_mask(unsigned long mmcr0_clear_mask)
{
	u64 val;

	/* 2) clear MMCR0[PMAO] - docs say BESCR[PMEO] should do this */
	/* 3) set MMCR0[PMAE]	- docs say BESCR[PME] should do this */
	val = mfspr(SPRN_MMCR0);
	mtspr(SPRN_MMCR0, (val & ~mmcr0_clear_mask) | MMCR0_PMAE);

	/* 4) clear BESCR[PMEO] */
	mtspr(SPRN_BESCRR, BESCR_PMEO);

	/* 5) set BESCR[PME] */
	mtspr(SPRN_BESCRS, BESCR_PME);

	/* 6) rfebb 1 - done in our caller */
}