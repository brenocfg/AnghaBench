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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_shim_info {int /*<<< orphan*/  wlc_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_b_mhf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
wlapi_bmac_mhf(struct phy_shim_info *physhim, u8 idx, u16 mask,
	       u16 val, int bands)
{
	brcms_b_mhf(physhim->wlc_hw, idx, mask, val, bands);
}