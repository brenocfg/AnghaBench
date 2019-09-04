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
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_typec_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TX_PSC_A0 (int /*<<< orphan*/ ) ; 
 scalar_t__ TX_PSC_A1 (int /*<<< orphan*/ ) ; 
 scalar_t__ TX_PSC_A2 (int /*<<< orphan*/ ) ; 
 scalar_t__ TX_PSC_A3 (int /*<<< orphan*/ ) ; 
 scalar_t__ TX_TXCC_MGNFS_MULT_000 (int /*<<< orphan*/ ) ; 
 scalar_t__ XCVR_DIAG_BIDI_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tcphy_tx_usb3_cfg_lane(struct rockchip_typec_phy *tcphy, u32 lane)
{
	writel(0x7799, tcphy->base + TX_PSC_A0(lane));
	writel(0x7798, tcphy->base + TX_PSC_A1(lane));
	writel(0x5098, tcphy->base + TX_PSC_A2(lane));
	writel(0x5098, tcphy->base + TX_PSC_A3(lane));
	writel(0, tcphy->base + TX_TXCC_MGNFS_MULT_000(lane));
	writel(0xbf, tcphy->base + XCVR_DIAG_BIDI_CTRL(lane));
}