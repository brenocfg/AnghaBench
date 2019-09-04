#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int src_mask; int dest_mask; int /*<<< orphan*/  nid; TYPE_1__* array; } ;
struct lola {TYPE_2__ mixer; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dest_mix_gain_enable; int /*<<< orphan*/ ** dest_mix_gain; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOLA_VERB_SET_MIX_GAIN ; 
 int /*<<< orphan*/  lola_codec_flush (struct lola*) ; 
 int lola_codec_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lola_mixer_set_mapping_gain(struct lola *chip,
				       unsigned int src, unsigned int dest,
				       unsigned short gain, bool on)
{
	unsigned int val;

	if (!(chip->mixer.src_mask & (1 << src)) ||
	    !(chip->mixer.dest_mask & (1 << dest)))
		return -EINVAL;
	if (on)
		writew(gain, &chip->mixer.array->dest_mix_gain[dest][src]);
	val = readl(&chip->mixer.array->dest_mix_gain_enable[dest]);
	if (on)
		val |= (1 << src);
	else
		val &= ~(1 << src);
	writel(val, &chip->mixer.array->dest_mix_gain_enable[dest]);
	lola_codec_flush(chip);
	return lola_codec_write(chip, chip->mixer.nid, LOLA_VERB_SET_MIX_GAIN,
				src, dest);
}