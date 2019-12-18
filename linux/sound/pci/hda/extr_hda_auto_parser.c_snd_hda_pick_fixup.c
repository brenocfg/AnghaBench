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
struct snd_pci_quirk {int value; char* name; int subdevice_mask; int subvendor; int subdevice; } ;
struct hda_model_fixup {char* name; int id; } ;
struct hda_fixup {int dummy; } ;
struct TYPE_4__ {unsigned int subsystem_id; int /*<<< orphan*/  chip_name; } ;
struct hda_codec {int fixup_id; char* fixup_name; struct hda_fixup const* fixup_list; TYPE_2__ core; TYPE_1__* bus; scalar_t__ modelname; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int HDA_FIXUP_ID_NOT_SET ; 
 int HDA_FIXUP_ID_NO_FIXUP ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,...) ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (int /*<<< orphan*/ ,struct snd_pci_quirk const*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

void snd_hda_pick_fixup(struct hda_codec *codec,
			const struct hda_model_fixup *models,
			const struct snd_pci_quirk *quirk,
			const struct hda_fixup *fixlist)
{
	const struct snd_pci_quirk *q;
	int id = HDA_FIXUP_ID_NOT_SET;
	const char *name = NULL;

	if (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		return;

	/* when model=nofixup is given, don't pick up any fixups */
	if (codec->modelname && !strcmp(codec->modelname, "nofixup")) {
		codec->fixup_list = NULL;
		codec->fixup_name = NULL;
		codec->fixup_id = HDA_FIXUP_ID_NO_FIXUP;
		codec_dbg(codec, "%s: picked no fixup (nofixup specified)\n",
			  codec->core.chip_name);
		return;
	}

	if (codec->modelname && models) {
		while (models->name) {
			if (!strcmp(codec->modelname, models->name)) {
				codec->fixup_id = models->id;
				codec->fixup_name = models->name;
				codec->fixup_list = fixlist;
				codec_dbg(codec, "%s: picked fixup %s (model specified)\n",
					  codec->core.chip_name, codec->fixup_name);
				return;
			}
			models++;
		}
	}
	if (quirk) {
		q = snd_pci_quirk_lookup(codec->bus->pci, quirk);
		if (q) {
			id = q->value;
#ifdef CONFIG_SND_DEBUG_VERBOSE
			name = q->name;
			codec_dbg(codec, "%s: picked fixup %s (PCI SSID%s)\n",
				  codec->core.chip_name, name, q->subdevice_mask ? "" : " - vendor generic");
#endif
		}
	}
	if (id < 0 && quirk) {
		for (q = quirk; q->subvendor || q->subdevice; q++) {
			unsigned int vendorid =
				q->subdevice | (q->subvendor << 16);
			unsigned int mask = 0xffff0000 | q->subdevice_mask;
			if ((codec->core.subsystem_id & mask) == (vendorid & mask)) {
				id = q->value;
#ifdef CONFIG_SND_DEBUG_VERBOSE
				name = q->name;
				codec_dbg(codec, "%s: picked fixup %s (codec SSID)\n",
					  codec->core.chip_name, name);
#endif
				break;
			}
		}
	}

	codec->fixup_id = id;
	if (id >= 0) {
		codec->fixup_list = fixlist;
		codec->fixup_name = name;
	}
}