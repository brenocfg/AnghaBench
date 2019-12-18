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
struct sata_oxnas_port_priv {scalar_t__ dmactl_base; } ;
struct ata_port {struct sata_oxnas_port_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ DMA_CONTROL ; 
 int /*<<< orphan*/  DMA_CONTROL_RESET ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void sata_oxnas_reset_dma(struct ata_port *ap, int assert)
{
	struct sata_oxnas_port_priv *pd = ap->private_data;
	u32 reg;

	reg = ioread32(pd->dmactl_base + DMA_CONTROL);
	if (assert)
		reg |= DMA_CONTROL_RESET;
	else
		reg &= ~DMA_CONTROL_RESET;

	iowrite32(reg, pd->dmactl_base + DMA_CONTROL);
}