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
typedef  int u32 ;
struct emac_adapter {int rfd_burst; scalar_t__ base; } ;

/* Variables and functions */
 int CUT_THRU_EN ; 
 scalar_t__ EMAC_RXQ_CTRL_0 ; 
 scalar_t__ EMAC_RXQ_CTRL_1 ; 
 scalar_t__ EMAC_RXQ_CTRL_2 ; 
 scalar_t__ EMAC_RXQ_CTRL_3 ; 
 int JUMBO_1KAH ; 
 int JUMBO_1KAH_BMSK ; 
 int JUMBO_1KAH_SHFT ; 
 int NUM_RFD_BURST_PREF_BMSK ; 
 int NUM_RFD_BURST_PREF_SHFT ; 
 int RFD_PREF_LOW_TH ; 
 int RFD_PREF_LOW_THRESHOLD_BMSK ; 
 int RFD_PREF_LOW_THRESHOLD_SHFT ; 
 int RFD_PREF_UP_TH ; 
 int RFD_PREF_UP_THRESHOLD_BMSK ; 
 int RFD_PREF_UP_THRESHOLD_SHFT ; 
 int RXD_TH ; 
 int RXD_THRESHOLD_BMSK ; 
 int RXD_THRESHOLD_SHFT ; 
 int RXD_TIMER_BMSK ; 
 int RXF_DOF_THRESFHOLD ; 
 int RXF_DOF_THRESHOLD_BMSK ; 
 int RXF_DOF_THRESHOLD_SHFT ; 
 int RXF_UOF_THRESFHOLD ; 
 int RXF_UOF_THRESHOLD_BMSK ; 
 int RXF_UOF_THRESHOLD_SHFT ; 
 int SP_IPV6 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emac_mac_rx_config(struct emac_adapter *adpt)
{
	u32 val;

	val = (adpt->rfd_burst << NUM_RFD_BURST_PREF_SHFT) &
	       NUM_RFD_BURST_PREF_BMSK;
	val |= (SP_IPV6 | CUT_THRU_EN);

	writel(val, adpt->base + EMAC_RXQ_CTRL_0);

	val = readl(adpt->base + EMAC_RXQ_CTRL_1);
	val &= ~(JUMBO_1KAH_BMSK | RFD_PREF_LOW_THRESHOLD_BMSK |
		 RFD_PREF_UP_THRESHOLD_BMSK);
	val |= (JUMBO_1KAH << JUMBO_1KAH_SHFT) |
		(RFD_PREF_LOW_TH << RFD_PREF_LOW_THRESHOLD_SHFT) |
		(RFD_PREF_UP_TH  << RFD_PREF_UP_THRESHOLD_SHFT);
	writel(val, adpt->base + EMAC_RXQ_CTRL_1);

	val = readl(adpt->base + EMAC_RXQ_CTRL_2);
	val &= ~(RXF_DOF_THRESHOLD_BMSK | RXF_UOF_THRESHOLD_BMSK);
	val |= (RXF_DOF_THRESFHOLD  << RXF_DOF_THRESHOLD_SHFT) |
		(RXF_UOF_THRESFHOLD << RXF_UOF_THRESHOLD_SHFT);
	writel(val, adpt->base + EMAC_RXQ_CTRL_2);

	val = readl(adpt->base + EMAC_RXQ_CTRL_3);
	val &= ~(RXD_TIMER_BMSK | RXD_THRESHOLD_BMSK);
	val |= RXD_TH << RXD_THRESHOLD_SHFT;
	writel(val, adpt->base + EMAC_RXQ_CTRL_3);
}