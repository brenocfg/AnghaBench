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
struct ca0132_spec {int cur_out_type; int ae5_headphone_gain_val; int /*<<< orphan*/  zxr_gain_set; } ;

/* Variables and functions */
 unsigned int FLOAT_ONE ; 
 unsigned int FLOAT_ZERO ; 
#define  HEADPHONE_OUT 135 
#define  QUIRK_AE5 134 
#define  QUIRK_R3D 133 
#define  QUIRK_R3DI 132 
#define  QUIRK_SBZ 131 
#define  QUIRK_ZXR 130 
 int /*<<< orphan*/  R3DI_HEADPHONE_OUT ; 
 int /*<<< orphan*/  R3DI_LINE_OUT ; 
#define  SPEAKER_OUT 129 
#define  SURROUND_OUT 128 
 int /*<<< orphan*/  ae5_headphone_gain_set (struct hda_codec*,int) ; 
 int /*<<< orphan*/  ae5_mmio_select_out (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0113_mmio_gpio_set (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  chipio_set_control_param (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  chipio_write (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 
 int /*<<< orphan*/  r3di_gpio_out_set (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxr_headphone_gain_set (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca0132_alt_select_out_quirk_handler(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int tmp;

	switch (spec->cur_out_type) {
	case SPEAKER_OUT:
		switch (ca0132_quirk(spec)) {
		case QUIRK_SBZ:
			ca0113_mmio_gpio_set(codec, 7, false);
			ca0113_mmio_gpio_set(codec, 4, true);
			ca0113_mmio_gpio_set(codec, 1, true);
			chipio_set_control_param(codec, 0x0d, 0x18);
			break;
		case QUIRK_ZXR:
			ca0113_mmio_gpio_set(codec, 2, true);
			ca0113_mmio_gpio_set(codec, 3, true);
			ca0113_mmio_gpio_set(codec, 5, false);
			zxr_headphone_gain_set(codec, 0);
			chipio_set_control_param(codec, 0x0d, 0x24);
			break;
		case QUIRK_R3DI:
			chipio_set_control_param(codec, 0x0d, 0x24);
			r3di_gpio_out_set(codec, R3DI_LINE_OUT);
			break;
		case QUIRK_R3D:
			chipio_set_control_param(codec, 0x0d, 0x24);
			ca0113_mmio_gpio_set(codec, 1, true);
			break;
		case QUIRK_AE5:
			ae5_mmio_select_out(codec);
			ae5_headphone_gain_set(codec, 2);
			tmp = FLOAT_ZERO;
			dspio_set_uint_param(codec, 0x96, 0x29, tmp);
			dspio_set_uint_param(codec, 0x96, 0x2a, tmp);
			chipio_set_control_param(codec, 0x0d, 0xa4);
			chipio_write(codec, 0x18b03c, 0x00000012);
			break;
		default:
			break;
		}
		break;
	case HEADPHONE_OUT:
		switch (ca0132_quirk(spec)) {
		case QUIRK_SBZ:
			ca0113_mmio_gpio_set(codec, 7, true);
			ca0113_mmio_gpio_set(codec, 4, true);
			ca0113_mmio_gpio_set(codec, 1, false);
			chipio_set_control_param(codec, 0x0d, 0x12);
			break;
		case QUIRK_ZXR:
			ca0113_mmio_gpio_set(codec, 2, false);
			ca0113_mmio_gpio_set(codec, 3, false);
			ca0113_mmio_gpio_set(codec, 5, true);
			zxr_headphone_gain_set(codec, spec->zxr_gain_set);
			chipio_set_control_param(codec, 0x0d, 0x21);
			break;
		case QUIRK_R3DI:
			chipio_set_control_param(codec, 0x0d, 0x21);
			r3di_gpio_out_set(codec, R3DI_HEADPHONE_OUT);
			break;
		case QUIRK_R3D:
			chipio_set_control_param(codec, 0x0d, 0x21);
			ca0113_mmio_gpio_set(codec, 0x1, false);
			break;
		case QUIRK_AE5:
			ae5_mmio_select_out(codec);
			ae5_headphone_gain_set(codec,
					spec->ae5_headphone_gain_val);
			tmp = FLOAT_ONE;
			dspio_set_uint_param(codec, 0x96, 0x29, tmp);
			dspio_set_uint_param(codec, 0x96, 0x2a, tmp);
			chipio_set_control_param(codec, 0x0d, 0xa1);
			chipio_write(codec, 0x18b03c, 0x00000012);
			break;
		default:
			break;
		}
		break;
	case SURROUND_OUT:
		switch (ca0132_quirk(spec)) {
		case QUIRK_SBZ:
			ca0113_mmio_gpio_set(codec, 7, false);
			ca0113_mmio_gpio_set(codec, 4, true);
			ca0113_mmio_gpio_set(codec, 1, true);
			chipio_set_control_param(codec, 0x0d, 0x18);
			break;
		case QUIRK_ZXR:
			ca0113_mmio_gpio_set(codec, 2, true);
			ca0113_mmio_gpio_set(codec, 3, true);
			ca0113_mmio_gpio_set(codec, 5, false);
			zxr_headphone_gain_set(codec, 0);
			chipio_set_control_param(codec, 0x0d, 0x24);
			break;
		case QUIRK_R3DI:
			chipio_set_control_param(codec, 0x0d, 0x24);
			r3di_gpio_out_set(codec, R3DI_LINE_OUT);
			break;
		case QUIRK_R3D:
			ca0113_mmio_gpio_set(codec, 1, true);
			chipio_set_control_param(codec, 0x0d, 0x24);
			break;
		case QUIRK_AE5:
			ae5_mmio_select_out(codec);
			ae5_headphone_gain_set(codec, 2);
			tmp = FLOAT_ZERO;
			dspio_set_uint_param(codec, 0x96, 0x29, tmp);
			dspio_set_uint_param(codec, 0x96, 0x2a, tmp);
			chipio_set_control_param(codec, 0x0d, 0xa4);
			chipio_write(codec, 0x18b03c, 0x00000012);
			break;
		default:
			break;
		}
		break;
	}
}