#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int src_mask; int /*<<< orphan*/  nid; TYPE_2__* array; } ;
struct lola {TYPE_3__ mixer; TYPE_1__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  src_gain_enable; int /*<<< orphan*/ * src_gain; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOLA_VERB_SET_SOURCE_GAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  lola_codec_flush (struct lola*) ; 
 int lola_codec_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ *) ; 
 unsigned short readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lola_mixer_set_src_gain(struct lola *chip, unsigned int id,
				   unsigned short gain, bool on)
{
	unsigned int oldval, val;

	if (!(chip->mixer.src_mask & (1 << id)))
		return -EINVAL;
	oldval = val = readl(&chip->mixer.array->src_gain_enable);
	if (on)
		val |= (1 << id);
	else
		val &= ~(1 << id);
	/* test if values unchanged */
	if ((val == oldval) &&
	    (gain == readw(&chip->mixer.array->src_gain[id])))
		return 0;

	dev_dbg(chip->card->dev,
		"lola_mixer_set_src_gain (id=%d, gain=%d) enable=%x\n",
			id, gain, val);
	writew(gain, &chip->mixer.array->src_gain[id]);
	writel(val, &chip->mixer.array->src_gain_enable);
	lola_codec_flush(chip);
	/* inform micro-controller about the new source gain */
	return lola_codec_write(chip, chip->mixer.nid,
				LOLA_VERB_SET_SOURCE_GAIN, id, 0);
}