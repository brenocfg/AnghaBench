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
struct hda_codec {struct ca0132_spec* spec; TYPE_1__* bus; } ;
struct ca0132_spec {struct ca0132_spec* spec_init_verbs; scalar_t__ mem_base; int /*<<< orphan*/  base_exit_verbs; int /*<<< orphan*/  unsol_hp_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
#define  QUIRK_AE5 132 
#define  QUIRK_R3D 131 
#define  QUIRK_R3DI 130 
#define  QUIRK_SBZ 129 
#define  QUIRK_ZXR 128 
 int /*<<< orphan*/  ae5_exit_chip (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_exit_chip (struct hda_codec*) ; 
 int ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ca0132_spec*) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r3d_exit_chip (struct hda_codec*) ; 
 int /*<<< orphan*/  r3di_gpio_shutdown (struct hda_codec*) ; 
 int /*<<< orphan*/  sbz_exit_chip (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxr_exit_chip (struct hda_codec*) ; 

__attribute__((used)) static void ca0132_free(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	cancel_delayed_work_sync(&spec->unsol_hp_work);
	snd_hda_power_up(codec);
	switch (ca0132_quirk(spec)) {
	case QUIRK_SBZ:
		sbz_exit_chip(codec);
		break;
	case QUIRK_ZXR:
		zxr_exit_chip(codec);
		break;
	case QUIRK_R3D:
		r3d_exit_chip(codec);
		break;
	case QUIRK_AE5:
		ae5_exit_chip(codec);
		break;
	case QUIRK_R3DI:
		r3di_gpio_shutdown(codec);
		break;
	default:
		break;
	}

	snd_hda_sequence_write(codec, spec->base_exit_verbs);
	ca0132_exit_chip(codec);

	snd_hda_power_down(codec);
#ifdef CONFIG_PCI
	if (spec->mem_base)
		pci_iounmap(codec->bus->pci, spec->mem_base);
#endif
	kfree(spec->spec_init_verbs);
	kfree(codec->spec);
}