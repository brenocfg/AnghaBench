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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; scalar_t__ dma_addr; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct fm801 {int cap_size; int cap_count; int cap_ctrl; int /*<<< orphan*/  reg_lock; scalar_t__ cap_buffer; scalar_t__ cap_pos; scalar_t__ cap_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_BUF1 ; 
 int /*<<< orphan*/  CAP_BUF2 ; 
 int /*<<< orphan*/  CAP_COUNT ; 
 int /*<<< orphan*/  CAP_CTRL ; 
 int FM801_16BIT ; 
 int FM801_RATE_MASK ; 
 int FM801_RATE_SHIFT ; 
 int FM801_START ; 
 int FM801_STEREO ; 
 int /*<<< orphan*/  fm801_writel (struct fm801*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fm801_writew (struct fm801*,int /*<<< orphan*/ ,int) ; 
 int snd_fm801_rate_bits (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct fm801* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_fm801_capture_prepare(struct snd_pcm_substream *substream)
{
	struct fm801 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	chip->cap_size = snd_pcm_lib_buffer_bytes(substream);
	chip->cap_count = snd_pcm_lib_period_bytes(substream);
	spin_lock_irq(&chip->reg_lock);
	chip->cap_ctrl &= ~(FM801_START | FM801_16BIT |
			     FM801_STEREO | FM801_RATE_MASK);
	if (snd_pcm_format_width(runtime->format) == 16)
		chip->cap_ctrl |= FM801_16BIT;
	if (runtime->channels > 1)
		chip->cap_ctrl |= FM801_STEREO;
	chip->cap_ctrl |= snd_fm801_rate_bits(runtime->rate) << FM801_RATE_SHIFT;
	chip->cap_buf = 0;
	fm801_writew(chip, CAP_CTRL, chip->cap_ctrl);
	fm801_writew(chip, CAP_COUNT, chip->cap_count - 1);
	chip->cap_buffer = runtime->dma_addr;
	chip->cap_pos = 0;
	fm801_writel(chip, CAP_BUF1, chip->cap_buffer);
	fm801_writel(chip, CAP_BUF2,
		     chip->cap_buffer + (chip->cap_count % chip->cap_size));
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}