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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int AHB_AXI_BUS_HALT_ACK ; 
 int AHB_AXI_BUS_HALT_REQ ; 
 int /*<<< orphan*/  ATH10K_AHB_AXI_BUS_HALT_TIMEOUT ; 
 int /*<<< orphan*/  ATH10K_DBG_AHB ; 
 int ath10k_ahb_tcsr_read32 (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_ahb_tcsr_write32 (struct ath10k*,int,int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void ath10k_ahb_halt_axi_bus(struct ath10k *ar, u32 haltreq_reg,
				    u32 haltack_reg)
{
	unsigned long timeout;
	u32 val;

	/* Issue halt axi bus request */
	val = ath10k_ahb_tcsr_read32(ar, haltreq_reg);
	val |= AHB_AXI_BUS_HALT_REQ;
	ath10k_ahb_tcsr_write32(ar, haltreq_reg, val);

	/* Wait for axi bus halted ack */
	timeout = jiffies + msecs_to_jiffies(ATH10K_AHB_AXI_BUS_HALT_TIMEOUT);
	do {
		val = ath10k_ahb_tcsr_read32(ar, haltack_reg);
		if (val & AHB_AXI_BUS_HALT_ACK)
			break;

		mdelay(1);
	} while (time_before(jiffies, timeout));

	if (!(val & AHB_AXI_BUS_HALT_ACK)) {
		ath10k_err(ar, "failed to halt axi bus: %d\n", val);
		return;
	}

	ath10k_dbg(ar, ATH10K_DBG_AHB, "axi bus halted\n");
}