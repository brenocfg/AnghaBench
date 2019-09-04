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
struct snd_sb {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  mode; int /*<<< orphan*/ * capture_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_MODE_CAPTURE ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sb16_csp_capture_close (struct snd_sb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb16_capture_close(struct snd_pcm_substream *substream)
{
	unsigned long flags;
	struct snd_sb *chip = snd_pcm_substream_chip(substream);

	snd_sb16_csp_capture_close(chip);
	spin_lock_irqsave(&chip->open_lock, flags);
	chip->capture_substream = NULL;
	chip->mode &= ~SB_MODE_CAPTURE;
	spin_unlock_irqrestore(&chip->open_lock, flags);
	return 0;
}