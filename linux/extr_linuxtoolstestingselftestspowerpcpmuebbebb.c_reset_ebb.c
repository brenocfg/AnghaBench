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

/* Variables and functions */
 int MMCR0_FC ; 
 int MMCR0_PMAO ; 
 int /*<<< orphan*/  reset_ebb_with_clear_mask (int) ; 

void reset_ebb(void)
{
	reset_ebb_with_clear_mask(MMCR0_PMAO | MMCR0_FC);
}