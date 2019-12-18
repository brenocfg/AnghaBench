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
struct TYPE_3__ {int /*<<< orphan*/  pins; int /*<<< orphan*/  (* func ) (struct hda_codec*,struct hda_fixup const*,int) ;int /*<<< orphan*/  verbs; } ;
struct hda_fixup {int chain_id; int type; scalar_t__ chained_before; int /*<<< orphan*/  chained; TYPE_1__ v; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip_name; } ;
struct hda_codec {char* fixup_name; TYPE_2__ core; struct hda_fixup* fixup_list; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int HDA_FIXUP_ACT_PROBE ; 
#define  HDA_FIXUP_FUNC 131 
#define  HDA_FIXUP_PINCTLS 130 
#define  HDA_FIXUP_PINS 129 
#define  HDA_FIXUP_VERBS 128 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pin_targets (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct hda_fixup const*,int) ; 

__attribute__((used)) static void apply_fixup(struct hda_codec *codec, int id, int action, int depth)
{
	const char *modelname = codec->fixup_name;

	while (id >= 0) {
		const struct hda_fixup *fix = codec->fixup_list + id;

		if (++depth > 10)
			break;
		if (fix->chained_before)
			apply_fixup(codec, fix->chain_id, action, depth + 1);

		switch (fix->type) {
		case HDA_FIXUP_PINS:
			if (action != HDA_FIXUP_ACT_PRE_PROBE || !fix->v.pins)
				break;
			codec_dbg(codec, "%s: Apply pincfg for %s\n",
				    codec->core.chip_name, modelname);
			snd_hda_apply_pincfgs(codec, fix->v.pins);
			break;
		case HDA_FIXUP_VERBS:
			if (action != HDA_FIXUP_ACT_PROBE || !fix->v.verbs)
				break;
			codec_dbg(codec, "%s: Apply fix-verbs for %s\n",
				    codec->core.chip_name, modelname);
			snd_hda_add_verbs(codec, fix->v.verbs);
			break;
		case HDA_FIXUP_FUNC:
			if (!fix->v.func)
				break;
			codec_dbg(codec, "%s: Apply fix-func for %s\n",
				    codec->core.chip_name, modelname);
			fix->v.func(codec, fix, action);
			break;
		case HDA_FIXUP_PINCTLS:
			if (action != HDA_FIXUP_ACT_PROBE || !fix->v.pins)
				break;
			codec_dbg(codec, "%s: Apply pinctl for %s\n",
				    codec->core.chip_name, modelname);
			set_pin_targets(codec, fix->v.pins);
			break;
		default:
			codec_err(codec, "%s: Invalid fixup type %d\n",
				   codec->core.chip_name, fix->type);
			break;
		}
		if (!fix->chained || fix->chained_before)
			break;
		id = fix->chain_id;
	}
}