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
struct snd_pcm_substream {int dummy; } ;
struct snd_bt87x {int /*<<< orphan*/  opened; int /*<<< orphan*/ * substream; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  reg_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_A_PWRDN ; 
 int /*<<< orphan*/  REG_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  snd_bt87x_writel (struct snd_bt87x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_bt87x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_bt87x_close(struct snd_pcm_substream *substream)
{
	struct snd_bt87x *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	chip->reg_control |= CTL_A_PWRDN;
	snd_bt87x_writel(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	spin_unlock_irq(&chip->reg_lock);

	chip->substream = NULL;
	clear_bit(0, &chip->opened);
	smp_mb__after_atomic();
	return 0;
}