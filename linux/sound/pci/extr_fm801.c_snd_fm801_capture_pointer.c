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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct fm801 {int cap_ctrl; int cap_pos; int cap_count; size_t cap_size; int /*<<< orphan*/  reg_lock; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_COUNT ; 
 int FM801_IRQ_CAPTURE ; 
 int FM801_START ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 int fm801_readw (struct fm801*,int /*<<< orphan*/ ) ; 
 struct fm801* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_fm801_capture_pointer(struct snd_pcm_substream *substream)
{
	struct fm801 *chip = snd_pcm_substream_chip(substream);
	size_t ptr;

	if (!(chip->cap_ctrl & FM801_START))
		return 0;
	spin_lock(&chip->reg_lock);
	ptr = chip->cap_pos + (chip->cap_count - 1) - fm801_readw(chip, CAP_COUNT);
	if (fm801_readw(chip, IRQ_STATUS) & FM801_IRQ_CAPTURE) {
		ptr += chip->cap_count;
		ptr %= chip->cap_size;
	}
	spin_unlock(&chip->reg_lock);
	return bytes_to_frames(substream->runtime, ptr);
}