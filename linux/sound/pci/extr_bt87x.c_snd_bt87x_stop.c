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
struct snd_bt87x {int reg_control; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int CTL_ACAP_EN ; 
 int CTL_FIFO_ENABLE ; 
 int CTL_RISC_ENABLE ; 
 int MY_INTERRUPTS ; 
 int /*<<< orphan*/  REG_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  REG_INT_MASK ; 
 int /*<<< orphan*/  REG_INT_STAT ; 
 int /*<<< orphan*/  snd_bt87x_writel (struct snd_bt87x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_bt87x_stop(struct snd_bt87x *chip)
{
	spin_lock(&chip->reg_lock);
	chip->reg_control &= ~(CTL_FIFO_ENABLE | CTL_RISC_ENABLE | CTL_ACAP_EN);
	snd_bt87x_writel(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	snd_bt87x_writel(chip, REG_INT_MASK, 0);
	snd_bt87x_writel(chip, REG_INT_STAT, MY_INTERRUPTS);
	spin_unlock(&chip->reg_lock);
	return 0;
}