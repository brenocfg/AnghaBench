#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lola_stream {int format_verb; int index; int /*<<< orphan*/  nid; } ;
struct lola {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOLA_VERB_SET_CHANNEL_STREAMID ; 
 int /*<<< orphan*/  LOLA_VERB_SET_STREAM_FORMAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int lola_codec_read (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lola_set_stream_config(struct lola *chip,
				  struct lola_stream *str,
				  int channels)
{
	int i, err;
	unsigned int verb, val;

	/* set format info for all channels
	 * (with only one command for the first channel)
	 */
	err = lola_codec_read(chip, str->nid, LOLA_VERB_SET_STREAM_FORMAT,
			      str->format_verb, 0, &val, NULL);
	if (err < 0) {
		dev_err(chip->card->dev, "Cannot set stream format 0x%x\n",
		       str->format_verb);
		return err;
	}

	/* update stream - channel config */
	for (i = 0; i < channels; i++) {
		verb = (str->index << 6) | i;
		err = lola_codec_read(chip, str[i].nid,
				      LOLA_VERB_SET_CHANNEL_STREAMID, 0, verb,
				      &val, NULL);
		if (err < 0) {
			dev_err(chip->card->dev,
				"Cannot set stream channel %d\n", i);
			return err;
		}
	}
	return 0;
}