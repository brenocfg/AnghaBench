#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int addr; } ;
struct snd_bt87x {int reg_control; int line_bytes; int lines; int interrupt_mask; int /*<<< orphan*/  reg_lock; TYPE_1__ dma_risc; scalar_t__ current_line; } ;

/* Variables and functions */
 int CTL_ACAP_EN ; 
 int CTL_FIFO_ENABLE ; 
 int CTL_RISC_ENABLE ; 
 int /*<<< orphan*/  REG_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  REG_INT_MASK ; 
 int /*<<< orphan*/  REG_PACKET_LEN ; 
 int /*<<< orphan*/  REG_RISC_STRT_ADD ; 
 int /*<<< orphan*/  snd_bt87x_writel (struct snd_bt87x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_bt87x_start(struct snd_bt87x *chip)
{
	spin_lock(&chip->reg_lock);
	chip->current_line = 0;
	chip->reg_control |= CTL_FIFO_ENABLE | CTL_RISC_ENABLE | CTL_ACAP_EN;
	snd_bt87x_writel(chip, REG_RISC_STRT_ADD, chip->dma_risc.addr);
	snd_bt87x_writel(chip, REG_PACKET_LEN,
			 chip->line_bytes | (chip->lines << 16));
	snd_bt87x_writel(chip, REG_INT_MASK, chip->interrupt_mask);
	snd_bt87x_writel(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	spin_unlock(&chip->reg_lock);
	return 0;
}