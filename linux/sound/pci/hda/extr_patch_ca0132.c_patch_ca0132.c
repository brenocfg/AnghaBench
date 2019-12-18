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
struct snd_pci_quirk {void* value; } ;
struct hda_codec {int pcm_format_first; int no_sticky_stream; TYPE_1__* bus; int /*<<< orphan*/  patch_ops; struct ca0132_spec* spec; } ;
struct ca0132_spec {int num_mixers; int use_alt_controls; int use_alt_functions; int use_pci_mmio; int /*<<< orphan*/  autocfg; int /*<<< orphan*/  unsol_hp_work; int /*<<< orphan*/  base_exit_verbs; int /*<<< orphan*/  base_init_verbs; void* quirk; int /*<<< orphan*/ * mem_base; void** mixers; int /*<<< orphan*/  dsp_state; struct hda_codec* codec; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_DOWNLOAD_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  QUIRK_AE5 133 
 void* QUIRK_NONE ; 
#define  QUIRK_R3D 132 
#define  QUIRK_R3DI 131 
#define  QUIRK_SBZ 130 
#define  QUIRK_ZXR 129 
#define  QUIRK_ZXR_DBPRO 128 
 int /*<<< orphan*/  ca0132_base_exit_verbs ; 
 int /*<<< orphan*/  ca0132_base_init_verbs ; 
 int /*<<< orphan*/  ca0132_config (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_free (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_init_chip (struct hda_codec*) ; 
 void* ca0132_mixer ; 
 int /*<<< orphan*/  ca0132_patch_ops ; 
 int ca0132_prepare_verbs (struct hda_codec*) ; 
 int ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  ca0132_quirks ; 
 int /*<<< orphan*/  ca0132_unsol_hp_delayed ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  codec_warn (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  dbpro_patch_ops ; 
 void* desktop_mixer ; 
 struct ca0132_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_iomap (int /*<<< orphan*/ ,int,int) ; 
 void* r3di_mixer ; 
 int /*<<< orphan*/  sbz_detect_quirk (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_set_name (struct hda_codec*,char*) ; 
 int snd_hda_parse_pin_def_config (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_ca0132(struct hda_codec *codec)
{
	struct ca0132_spec *spec;
	int err;
	const struct snd_pci_quirk *quirk;

	codec_dbg(codec, "patch_ca0132\n");

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	codec->spec = spec;
	spec->codec = codec;

	/* Detect codec quirk */
	quirk = snd_pci_quirk_lookup(codec->bus->pci, ca0132_quirks);
	if (quirk)
		spec->quirk = quirk->value;
	else
		spec->quirk = QUIRK_NONE;
	if (ca0132_quirk(spec) == QUIRK_SBZ)
		sbz_detect_quirk(codec);

	if (ca0132_quirk(spec) == QUIRK_ZXR_DBPRO)
		codec->patch_ops = dbpro_patch_ops;
	else
		codec->patch_ops = ca0132_patch_ops;

	codec->pcm_format_first = 1;
	codec->no_sticky_stream = 1;


	spec->dsp_state = DSP_DOWNLOAD_INIT;
	spec->num_mixers = 1;

	/* Set which mixers each quirk uses. */
	switch (ca0132_quirk(spec)) {
	case QUIRK_SBZ:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound Blaster Z");
		break;
	case QUIRK_ZXR:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound Blaster ZxR");
		break;
	case QUIRK_ZXR_DBPRO:
		break;
	case QUIRK_R3D:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Recon3D");
		break;
	case QUIRK_R3DI:
		spec->mixers[0] = r3di_mixer;
		snd_hda_codec_set_name(codec, "Recon3Di");
		break;
	case QUIRK_AE5:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound BlasterX AE-5");
		break;
	default:
		spec->mixers[0] = ca0132_mixer;
		break;
	}

	/* Setup whether or not to use alt functions/controls/pci_mmio */
	switch (ca0132_quirk(spec)) {
	case QUIRK_SBZ:
	case QUIRK_R3D:
	case QUIRK_AE5:
	case QUIRK_ZXR:
		spec->use_alt_controls = true;
		spec->use_alt_functions = true;
		spec->use_pci_mmio = true;
		break;
	case QUIRK_R3DI:
		spec->use_alt_controls = true;
		spec->use_alt_functions = true;
		spec->use_pci_mmio = false;
		break;
	default:
		spec->use_alt_controls = false;
		spec->use_alt_functions = false;
		spec->use_pci_mmio = false;
		break;
	}

#ifdef CONFIG_PCI
	if (spec->use_pci_mmio) {
		spec->mem_base = pci_iomap(codec->bus->pci, 2, 0xC20);
		if (spec->mem_base == NULL) {
			codec_warn(codec, "pci_iomap failed! Setting quirk to QUIRK_NONE.");
			spec->quirk = QUIRK_NONE;
		}
	}
#endif

	spec->base_init_verbs = ca0132_base_init_verbs;
	spec->base_exit_verbs = ca0132_base_exit_verbs;

	INIT_DELAYED_WORK(&spec->unsol_hp_work, ca0132_unsol_hp_delayed);

	ca0132_init_chip(codec);

	ca0132_config(codec);

	err = ca0132_prepare_verbs(codec);
	if (err < 0)
		goto error;

	err = snd_hda_parse_pin_def_config(codec, &spec->autocfg, NULL);
	if (err < 0)
		goto error;

	return 0;

 error:
	ca0132_free(codec);
	return err;
}