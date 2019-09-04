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
struct emac_adapter {int tpd_burst; scalar_t__ base; } ;

/* Variables and functions */
 int EMAC_MAX_TX_OFFLOAD_THRESH ; 
 scalar_t__ EMAC_TXQ_CTRL_0 ; 
 scalar_t__ EMAC_TXQ_CTRL_1 ; 
 scalar_t__ EMAC_TXQ_CTRL_2 ; 
 int JUMBO_TASK_OFFLOAD_THRESHOLD_BMSK ; 
 int LS_8023_SP ; 
 int NUM_TPD_BURST_PREF_BMSK ; 
 int NUM_TPD_BURST_PREF_SHFT ; 
 int NUM_TXF_BURST_PREF_BMSK ; 
 int NUM_TXF_BURST_PREF_SHFT ; 
 int TXF_HWM_BMSK ; 
 int TXF_LWM_BMSK ; 
 int TXQ_MODE ; 
 int /*<<< orphan*/  emac_reg_update32 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emac_mac_tx_config(struct emac_adapter *adpt)
{
	u32 val;

	writel((EMAC_MAX_TX_OFFLOAD_THRESH >> 3) &
	       JUMBO_TASK_OFFLOAD_THRESHOLD_BMSK, adpt->base + EMAC_TXQ_CTRL_1);

	val = (adpt->tpd_burst << NUM_TPD_BURST_PREF_SHFT) &
	       NUM_TPD_BURST_PREF_BMSK;

	val |= TXQ_MODE | LS_8023_SP;
	val |= (0x0100 << NUM_TXF_BURST_PREF_SHFT) &
		NUM_TXF_BURST_PREF_BMSK;

	writel(val, adpt->base + EMAC_TXQ_CTRL_0);
	emac_reg_update32(adpt->base + EMAC_TXQ_CTRL_2,
			  (TXF_HWM_BMSK | TXF_LWM_BMSK), 0);
}