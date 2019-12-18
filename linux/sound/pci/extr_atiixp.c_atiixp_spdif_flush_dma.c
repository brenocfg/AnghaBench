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
struct atiixp {int dummy; } ;

/* Variables and functions */
 int ATI_REG_DMA_FIFO_USED ; 
 int /*<<< orphan*/  SPDF_DMA_DT_SIZE ; 
 int atiixp_read (struct atiixp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_spdif_enable_dma (struct atiixp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_spdif_enable_transfer (struct atiixp*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void atiixp_spdif_flush_dma(struct atiixp *chip)
{
	int timeout;

	/* DMA off, transfer on */
	atiixp_spdif_enable_dma(chip, 0);
	atiixp_spdif_enable_transfer(chip, 1);
	
	timeout = 100;
	do {
		if (! (atiixp_read(chip, SPDF_DMA_DT_SIZE) & ATI_REG_DMA_FIFO_USED))
			break;
		udelay(1);
	} while (timeout-- > 0);

	atiixp_spdif_enable_transfer(chip, 0);
}