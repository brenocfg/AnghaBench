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
struct lola {unsigned int input_src_caps_mask; unsigned int input_src_mask; TYPE_3__* pcm; TYPE_1__* pin; } ;
struct TYPE_6__ {TYPE_2__* streams; } ;
struct TYPE_5__ {int /*<<< orphan*/  nid; } ;
struct TYPE_4__ {int num_pins; } ;

/* Variables and functions */
 size_t CAPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOLA_VERB_SET_SRC ; 
 int lola_codec_flush (struct lola*) ; 
 int lola_codec_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

int lola_set_src_config(struct lola *chip, unsigned int src_mask, bool update)
{
	int ret = 0;
	int success = 0;
	int n, err;

	/* SRC can be activated and the dwInputSRCMask is valid? */
	if ((chip->input_src_caps_mask & src_mask) != src_mask)
		return -EINVAL;
	/* handle all even Inputs - SRC is a stereo setting !!! */
	for (n = 0; n < chip->pin[CAPT].num_pins; n += 2) {
		unsigned int mask = 3U << n; /* handle the stereo case */
		unsigned int new_src, src_state;
		if (!(chip->input_src_caps_mask & mask))
			continue;
		/* if one IO needs SRC, both stereo IO will get SRC */
		new_src = (src_mask & mask) != 0;
		if (update) {
			src_state = (chip->input_src_mask & mask) != 0;
			if (src_state == new_src)
				continue;   /* nothing to change for this IO */
		}
		err = lola_codec_write(chip, chip->pcm[CAPT].streams[n].nid,
				       LOLA_VERB_SET_SRC, new_src, 0);
		if (!err)
			success++;
		else
			ret = err;
	}
	if (success)
		ret = lola_codec_flush(chip);
	if (!ret)
		chip->input_src_mask = src_mask;
	return ret;
}