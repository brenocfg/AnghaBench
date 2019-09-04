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
struct cas {int cas_flags; int /*<<< orphan*/ * stat_lock; scalar_t__ regs; } ;

/* Variables and functions */
 int CAS_FLAG_TARGET_ABORT ; 
 scalar_t__ CAS_HP_ALT_FIRMWARE ; 
 scalar_t__ CAS_HP_FIRMWARE ; 
 size_t N_TX_RINGS ; 
 scalar_t__ REG_RX_CFG ; 
 scalar_t__ REG_TX_CFG ; 
 int /*<<< orphan*/  RX_CFG_DMA_EN ; 
 int /*<<< orphan*/  TX_CFG_DMA_EN ; 
 int /*<<< orphan*/  cas_clear_mac_err (struct cas*) ; 
 int /*<<< orphan*/  cas_entropy_reset (struct cas*) ; 
 int /*<<< orphan*/  cas_global_reset (struct cas*,int) ; 
 int /*<<< orphan*/  cas_load_firmware (struct cas*,scalar_t__) ; 
 int /*<<< orphan*/  cas_mac_reset (struct cas*) ; 
 int /*<<< orphan*/  cas_mask_intr (struct cas*) ; 
 scalar_t__ cas_prog_null ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cas_reset(struct cas *cp, int blkflag)
{
	u32 val;

	cas_mask_intr(cp);
	cas_global_reset(cp, blkflag);
	cas_mac_reset(cp);
	cas_entropy_reset(cp);

	/* disable dma engines. */
	val = readl(cp->regs + REG_TX_CFG);
	val &= ~TX_CFG_DMA_EN;
	writel(val, cp->regs + REG_TX_CFG);

	val = readl(cp->regs + REG_RX_CFG);
	val &= ~RX_CFG_DMA_EN;
	writel(val, cp->regs + REG_RX_CFG);

	/* program header parser */
	if ((cp->cas_flags & CAS_FLAG_TARGET_ABORT) ||
	    (CAS_HP_ALT_FIRMWARE == cas_prog_null)) {
		cas_load_firmware(cp, CAS_HP_FIRMWARE);
	} else {
		cas_load_firmware(cp, CAS_HP_ALT_FIRMWARE);
	}

	/* clear out error registers */
	spin_lock(&cp->stat_lock[N_TX_RINGS]);
	cas_clear_mac_err(cp);
	spin_unlock(&cp->stat_lock[N_TX_RINGS]);
}