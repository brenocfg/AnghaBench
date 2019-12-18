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
struct snd_ad1816a {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_CAPTURE_CONFIG ; 
 int AD1816A_CAPTURE_ENABLE ; 
 int AD1816A_CAPTURE_NOT_EQUAL ; 
 int AD1816A_CAPTURE_PIO ; 
 int /*<<< orphan*/  AD1816A_CHIP_CONFIG ; 
 int /*<<< orphan*/  AD1816A_DSP_CONFIG ; 
 int /*<<< orphan*/  AD1816A_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  AD1816A_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  AD1816A_PLAYBACK_CONFIG ; 
 int AD1816A_PLAYBACK_ENABLE ; 
 int AD1816A_PLAYBACK_PIO ; 
 int /*<<< orphan*/  AD1816A_POWERDOWN_CTRL ; 
 int AD1816A_WSS_ENABLE ; 
 int /*<<< orphan*/  snd_ad1816a_out (struct snd_ad1816a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ad1816a_out_mask (struct snd_ad1816a*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_ad1816a_write (struct snd_ad1816a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ad1816a_write_mask (struct snd_ad1816a*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ad1816a_init(struct snd_ad1816a *chip)
{
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);

	snd_ad1816a_out(chip, AD1816A_INTERRUPT_STATUS, 0x00);
	snd_ad1816a_out_mask(chip, AD1816A_PLAYBACK_CONFIG,
		AD1816A_PLAYBACK_ENABLE | AD1816A_PLAYBACK_PIO, 0x00);
	snd_ad1816a_out_mask(chip, AD1816A_CAPTURE_CONFIG,
		AD1816A_CAPTURE_ENABLE | AD1816A_CAPTURE_PIO, 0x00);
	snd_ad1816a_write(chip, AD1816A_INTERRUPT_ENABLE, 0x0000);
	snd_ad1816a_write_mask(chip, AD1816A_CHIP_CONFIG,
		AD1816A_CAPTURE_NOT_EQUAL | AD1816A_WSS_ENABLE, 0xffff);
	snd_ad1816a_write(chip, AD1816A_DSP_CONFIG, 0x0000);
	snd_ad1816a_write(chip, AD1816A_POWERDOWN_CTRL, 0x0000);

	spin_unlock_irqrestore(&chip->lock, flags);
}