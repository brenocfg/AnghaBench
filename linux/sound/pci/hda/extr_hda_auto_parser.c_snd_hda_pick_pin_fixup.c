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
struct snd_hda_pin_quirk {int subvendor; scalar_t__ codec; int /*<<< orphan*/  name; int /*<<< orphan*/  value; int /*<<< orphan*/  pins; } ;
struct hda_fixup {int dummy; } ;
struct TYPE_2__ {int subsystem_id; scalar_t__ vendor_id; int /*<<< orphan*/  chip_name; } ;
struct hda_codec {struct hda_fixup const* fixup_list; int /*<<< orphan*/  fixup_name; TYPE_1__ core; int /*<<< orphan*/  fixup_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_FIXUP_ID_NOT_SET ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pin_config_match (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

void snd_hda_pick_pin_fixup(struct hda_codec *codec,
			    const struct snd_hda_pin_quirk *pin_quirk,
			    const struct hda_fixup *fixlist,
			    bool match_all_pins)
{
	const struct snd_hda_pin_quirk *pq;

	if (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		return;

	for (pq = pin_quirk; pq->subvendor; pq++) {
		if ((codec->core.subsystem_id & 0xffff0000) != (pq->subvendor << 16))
			continue;
		if (codec->core.vendor_id != pq->codec)
			continue;
		if (pin_config_match(codec, pq->pins, match_all_pins)) {
			codec->fixup_id = pq->value;
#ifdef CONFIG_SND_DEBUG_VERBOSE
			codec->fixup_name = pq->name;
			codec_dbg(codec, "%s: picked fixup %s (pin match)\n",
				  codec->core.chip_name, codec->fixup_name);
#endif
			codec->fixup_list = fixlist;
			return;
		}
	}
}