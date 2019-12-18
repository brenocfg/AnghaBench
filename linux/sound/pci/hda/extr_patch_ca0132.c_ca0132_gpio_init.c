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
#define  QUIRK_AE5 130 
#define  QUIRK_R3DI 129 
#define  QUIRK_SBZ 128 
 int ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ca0132_gpio_init(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	switch (ca0132_quirk(spec)) {
	case QUIRK_SBZ:
	case QUIRK_AE5:
		snd_hda_codec_write(codec, 0x01, 0, 0x793, 0x00);
		snd_hda_codec_write(codec, 0x01, 0, 0x794, 0x53);
		snd_hda_codec_write(codec, 0x01, 0, 0x790, 0x23);
		break;
	case QUIRK_R3DI:
		snd_hda_codec_write(codec, 0x01, 0, 0x793, 0x00);
		snd_hda_codec_write(codec, 0x01, 0, 0x794, 0x5B);
		break;
	default:
		break;
	}

}