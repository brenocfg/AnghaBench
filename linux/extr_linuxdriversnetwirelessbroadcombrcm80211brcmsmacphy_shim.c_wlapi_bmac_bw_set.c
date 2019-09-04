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
typedef  int /*<<< orphan*/  u16 ;
struct phy_shim_info {int /*<<< orphan*/  wlc_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_b_bw_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wlapi_bmac_bw_set(struct phy_shim_info *physhim, u16 bw)
{
	brcms_b_bw_set(physhim->wlc_hw, bw);
}