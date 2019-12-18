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
struct lola_sample_clock {unsigned char type; int format; unsigned int freq; } ;
struct TYPE_4__ {int nid; unsigned int items; int cur_index; int cur_freq; int cur_valid; int* idx_lookup; struct lola_sample_clock* sample_clock; } ;
struct lola {unsigned int sample_rate_min; TYPE_2__ clock; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int LOLA_CLOCK_FORMAT_NONE ; 
 int LOLA_CLOCK_FORMAT_NTSC ; 
 int LOLA_CLOCK_FORMAT_PAL ; 
 unsigned char LOLA_CLOCK_TYPE_INTERNAL ; 
 unsigned char LOLA_CLOCK_TYPE_VIDEO ; 
 int /*<<< orphan*/  LOLA_PAR_AUDIO_WIDGET_CAP ; 
 int /*<<< orphan*/  LOLA_VERB_GET_CLOCK_LIST ; 
 unsigned int MAX_SAMPLE_CLOCK_COUNT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int lola_codec_read (struct lola*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int lola_read_param (struct lola*,int,int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int lola_sample_rate_convert (unsigned int) ; 

int lola_init_clock_widget(struct lola *chip, int nid)
{
	unsigned int val;
	int i, j, nitems, nb_verbs, idx, idx_list;
	int err;

	err = lola_read_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't read wcaps for 0x%x\n", nid);
		return err;
	}

	if ((val & 0xfff00000) != 0x01f00000) { /* test SubType and Type */
		dev_dbg(chip->card->dev, "No valid clock widget\n");
		return 0;
	}

	chip->clock.nid = nid;
	chip->clock.items = val & 0xff;
	dev_dbg(chip->card->dev, "clock_list nid=%x, entries=%d\n", nid,
		    chip->clock.items);
	if (chip->clock.items > MAX_SAMPLE_CLOCK_COUNT) {
		dev_err(chip->card->dev, "CLOCK_LIST too big: %d\n",
		       chip->clock.items);
		return -EINVAL;
	}

	nitems = chip->clock.items;
	nb_verbs = (nitems + 3) / 4;
	idx = 0;
	idx_list = 0;
	for (i = 0; i < nb_verbs; i++) {
		unsigned int res_ex;
		unsigned short items[4];

		err = lola_codec_read(chip, nid, LOLA_VERB_GET_CLOCK_LIST,
				      idx, 0, &val, &res_ex);
		if (err < 0) {
			dev_err(chip->card->dev, "Can't read CLOCK_LIST\n");
			return -EINVAL;
		}

		items[0] = val & 0xfff;
		items[1] = (val >> 16) & 0xfff;
		items[2] = res_ex & 0xfff;
		items[3] = (res_ex >> 16) & 0xfff;

		for (j = 0; j < 4; j++) {
			unsigned char type = items[j] >> 8;
			unsigned int freq = items[j] & 0xff;
			int format = LOLA_CLOCK_FORMAT_NONE;
			bool add_clock = true;
			if (type == LOLA_CLOCK_TYPE_INTERNAL) {
				freq = lola_sample_rate_convert(freq);
				if (freq < chip->sample_rate_min)
					add_clock = false;
				else if (freq == 48000) {
					chip->clock.cur_index = idx_list;
					chip->clock.cur_freq = 48000;
					chip->clock.cur_valid = true;
				}
			} else if (type == LOLA_CLOCK_TYPE_VIDEO) {
				freq = lola_sample_rate_convert(freq);
				if (freq < chip->sample_rate_min)
					add_clock = false;
				/* video clock has a format (0:NTSC, 1:PAL)*/
				if (items[j] & 0x80)
					format = LOLA_CLOCK_FORMAT_NTSC;
				else
					format = LOLA_CLOCK_FORMAT_PAL;
			}
			if (add_clock) {
				struct lola_sample_clock *sc;
				sc = &chip->clock.sample_clock[idx_list];
				sc->type = type;
				sc->format = format;
				sc->freq = freq;
				/* keep the index used with the board */
				chip->clock.idx_lookup[idx_list] = idx;
				idx_list++;
			} else {
				chip->clock.items--;
			}
			if (++idx >= nitems)
				break;
		}
	}
	return 0;
}