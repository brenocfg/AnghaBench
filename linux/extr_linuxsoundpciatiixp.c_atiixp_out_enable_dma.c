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
 unsigned int ATI_REG_CMD_OUT_DMA_EN ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  atiixp_out_flush_dma (struct atiixp*) ; 
 unsigned int atiixp_read (struct atiixp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void atiixp_out_enable_dma(struct atiixp *chip, int on)
{
	unsigned int data;
	data = atiixp_read(chip, CMD);
	if (on) {
		if (data & ATI_REG_CMD_OUT_DMA_EN)
			return;
		atiixp_out_flush_dma(chip);
		data |= ATI_REG_CMD_OUT_DMA_EN;
	} else
		data &= ~ATI_REG_CMD_OUT_DMA_EN;
	atiixp_write(chip, CMD, data);
}