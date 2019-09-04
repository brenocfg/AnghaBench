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
struct intel8x0 {int /*<<< orphan*/  reg_lock; scalar_t__ inside_vm; } ;
struct ichdev {unsigned int position; size_t last_pos; size_t pos_shift; size_t fragsize1; size_t size; scalar_t__ roff_picb; scalar_t__ reg_offset; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ ICH_REG_OFF_CIV ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 struct ichdev* get_ichdev (struct snd_pcm_substream*) ; 
 int igetbyte (struct intel8x0*,scalar_t__) ; 
 size_t igetword (struct intel8x0*,scalar_t__) ; 
 struct intel8x0* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_intel8x0_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct intel8x0 *chip = snd_pcm_substream_chip(substream);
	struct ichdev *ichdev = get_ichdev(substream);
	size_t ptr1, ptr;
	int civ, timeout = 10;
	unsigned int position;

	spin_lock(&chip->reg_lock);
	do {
		civ = igetbyte(chip, ichdev->reg_offset + ICH_REG_OFF_CIV);
		ptr1 = igetword(chip, ichdev->reg_offset + ichdev->roff_picb);
		position = ichdev->position;
		if (ptr1 == 0) {
			udelay(10);
			continue;
		}
		if (civ != igetbyte(chip, ichdev->reg_offset + ICH_REG_OFF_CIV))
			continue;

		/* IO read operation is very expensive inside virtual machine
		 * as it is emulated. The probability that subsequent PICB read
		 * will return different result is high enough to loop till
		 * timeout here.
		 * Same CIV is strict enough condition to be sure that PICB
		 * is valid inside VM on emulated card. */
		if (chip->inside_vm)
			break;
		if (ptr1 == igetword(chip, ichdev->reg_offset + ichdev->roff_picb))
			break;
	} while (timeout--);
	ptr = ichdev->last_pos;
	if (ptr1 != 0) {
		ptr1 <<= ichdev->pos_shift;
		ptr = ichdev->fragsize1 - ptr1;
		ptr += position;
		if (ptr < ichdev->last_pos) {
			unsigned int pos_base, last_base;
			pos_base = position / ichdev->fragsize1;
			last_base = ichdev->last_pos / ichdev->fragsize1;
			/* another sanity check; ptr1 can go back to full
			 * before the base position is updated
			 */
			if (pos_base == last_base)
				ptr = ichdev->last_pos;
		}
	}
	ichdev->last_pos = ptr;
	spin_unlock(&chip->reg_lock);
	if (ptr >= ichdev->size)
		return 0;
	return bytes_to_frames(substream->runtime, ptr);
}