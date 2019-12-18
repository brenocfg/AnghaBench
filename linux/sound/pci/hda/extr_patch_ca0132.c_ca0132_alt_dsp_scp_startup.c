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
struct ca0132_spec {int dummy; } ;

/* Variables and functions */
#define  QUIRK_AE5 131 
#define  QUIRK_R3D 130 
#define  QUIRK_R3DI 129 
#define  QUIRK_SBZ 128 
 int ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  dspio_set_uint_param_no_source (struct hda_codec*,int,int,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ca0132_alt_dsp_scp_startup(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int tmp, i;

	/*
	 * Gotta run these twice, or else mic works inconsistently. Not clear
	 * why this is, but multiple tests have confirmed it.
	 */
	for (i = 0; i < 2; i++) {
		switch (ca0132_quirk(spec)) {
		case QUIRK_SBZ:
		case QUIRK_AE5:
			tmp = 0x00000003;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			tmp = 0x00000000;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0A, tmp);
			tmp = 0x00000001;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0B, tmp);
			tmp = 0x00000004;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			tmp = 0x00000005;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			tmp = 0x00000000;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			break;
		case QUIRK_R3D:
		case QUIRK_R3DI:
			tmp = 0x00000000;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0A, tmp);
			tmp = 0x00000001;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0B, tmp);
			tmp = 0x00000004;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			tmp = 0x00000005;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			tmp = 0x00000000;
			dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);
			break;
		default:
			break;
		}
		msleep(100);
	}
}