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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_FW (char*) ; 
 int /*<<< orphan*/  IPW_DMA_I_CB_BASE ; 
 int /*<<< orphan*/  IPW_SHARED_SRAM_DMA_CONTROL ; 
 int /*<<< orphan*/  ipw_fw_dma_reset_command_blocks (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_fw_dma_enable(struct ipw_priv *priv)
{				/* start dma engine but no transfers yet */

	IPW_DEBUG_FW(">> :\n");

	/* Start the dma */
	ipw_fw_dma_reset_command_blocks(priv);

	/* Write CB base address */
	ipw_write_reg32(priv, IPW_DMA_I_CB_BASE, IPW_SHARED_SRAM_DMA_CONTROL);

	IPW_DEBUG_FW("<< :\n");
	return 0;
}