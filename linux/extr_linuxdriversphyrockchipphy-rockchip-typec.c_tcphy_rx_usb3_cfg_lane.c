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
 scalar_t__ RX_DIAG_SIGDET_TUNE (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_PSC_A0 (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_PSC_A1 (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_PSC_A2 (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_PSC_A3 (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_PSC_CAL (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_PSC_RDY (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_REE_CTRL_DATA_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_SIGDET_HL_FILT_TMR (int /*<<< orphan*/ ) ; 
 scalar_t__ XCVR_DIAG_BIDI_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tcphy_rx_usb3_cfg_lane(struct rockchip_typec_phy *tcphy, u32 lane)
{
	writel(0xa6fd, tcphy->base + RX_PSC_A0(lane));
	writel(0xa6fd, tcphy->base + RX_PSC_A1(lane));
	writel(0xa410, tcphy->base + RX_PSC_A2(lane));
	writel(0x2410, tcphy->base + RX_PSC_A3(lane));
	writel(0x23ff, tcphy->base + RX_PSC_CAL(lane));
	writel(0x13, tcphy->base + RX_SIGDET_HL_FILT_TMR(lane));
	writel(0x03e7, tcphy->base + RX_REE_CTRL_DATA_MASK(lane));
	writel(0x1004, tcphy->base + RX_DIAG_SIGDET_TUNE(lane));
	writel(0x2010, tcphy->base + RX_PSC_RDY(lane));
	writel(0xfb, tcphy->base + XCVR_DIAG_BIDI_CTRL(lane));
}