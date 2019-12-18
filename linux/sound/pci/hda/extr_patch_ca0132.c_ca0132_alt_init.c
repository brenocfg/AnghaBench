#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  desktop_init_verbs; int /*<<< orphan*/  chip_init_verbs; } ;

/* Variables and functions */
#define  QUIRK_AE5 132 
#define  QUIRK_R3D 131 
#define  QUIRK_R3DI 130 
#define  QUIRK_SBZ 129 
#define  QUIRK_ZXR 128 
 int /*<<< orphan*/  R3DI_DSP_DOWNLOADING ; 
 int VENDOR_CHIPIO_8051_ADDRESS_LOW ; 
 int VENDOR_CHIPIO_PLL_PMU_WRITE ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int /*<<< orphan*/  ca0113_mmio_command_set (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  ca0132_alt_vol_setup (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_gpio_init (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_gpio_setup (struct hda_codec*) ; 
 int ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  chipio_write (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  r3d_pre_dsp_setup (struct hda_codec*) ; 
 int /*<<< orphan*/  r3di_gpio_dsp_status_set (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r3di_pre_dsp_setup (struct hda_codec*) ; 
 int /*<<< orphan*/  sbz_pre_dsp_setup (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca0132_alt_init(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	ca0132_alt_vol_setup(codec);

	switch (ca0132_quirk(spec)) {
	case QUIRK_SBZ:
		codec_dbg(codec, "SBZ alt_init");
		ca0132_gpio_init(codec);
		sbz_pre_dsp_setup(codec);
		snd_hda_sequence_write(codec, spec->chip_init_verbs);
		snd_hda_sequence_write(codec, spec->desktop_init_verbs);
		break;
	case QUIRK_R3DI:
		codec_dbg(codec, "R3DI alt_init");
		ca0132_gpio_init(codec);
		ca0132_gpio_setup(codec);
		r3di_gpio_dsp_status_set(codec, R3DI_DSP_DOWNLOADING);
		r3di_pre_dsp_setup(codec);
		snd_hda_sequence_write(codec, spec->chip_init_verbs);
		snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0, 0x6FF, 0xC4);
		break;
	case QUIRK_R3D:
		r3d_pre_dsp_setup(codec);
		snd_hda_sequence_write(codec, spec->chip_init_verbs);
		snd_hda_sequence_write(codec, spec->desktop_init_verbs);
		break;
	case QUIRK_AE5:
		ca0132_gpio_init(codec);
		snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
				VENDOR_CHIPIO_8051_ADDRESS_LOW, 0x49);
		snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
				VENDOR_CHIPIO_PLL_PMU_WRITE, 0x88);
		chipio_write(codec, 0x18b030, 0x00000020);
		snd_hda_sequence_write(codec, spec->chip_init_verbs);
		snd_hda_sequence_write(codec, spec->desktop_init_verbs);
		ca0113_mmio_command_set(codec, 0x30, 0x32, 0x3f);
		break;
	case QUIRK_ZXR:
		snd_hda_sequence_write(codec, spec->chip_init_verbs);
		snd_hda_sequence_write(codec, spec->desktop_init_verbs);
		break;
	default:
		break;
	}
}