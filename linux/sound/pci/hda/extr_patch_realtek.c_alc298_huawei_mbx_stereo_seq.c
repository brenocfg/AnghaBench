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
struct hda_codec {int dummy; } ;
struct hda_alc298_mbxinit {int value_0x23; int value_0x25; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_PIN_SENSE ; 
 int /*<<< orphan*/  AC_VERB_SET_COEF_INDEX ; 
 int /*<<< orphan*/  AC_VERB_SET_DIGI_CONVERT_3 ; 
 int /*<<< orphan*/  AC_VERB_SET_PROC_COEF ; 
 int /*<<< orphan*/  alc_write_coef_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void alc298_huawei_mbx_stereo_seq(struct hda_codec *codec,
					 const struct hda_alc298_mbxinit *initval,
					 bool first)
{
	snd_hda_codec_write(codec, 0x06, 0, AC_VERB_SET_DIGI_CONVERT_3, 0x0);
	alc_write_coef_idx(codec, 0x26, 0xb000);

	if (first)
		snd_hda_codec_write(codec, 0x21, 0, AC_VERB_GET_PIN_SENSE, 0x0);

	snd_hda_codec_write(codec, 0x6, 0, AC_VERB_SET_DIGI_CONVERT_3, 0x80);
	alc_write_coef_idx(codec, 0x26, 0xf000);
	alc_write_coef_idx(codec, 0x23, initval->value_0x23);

	if (initval->value_0x23 != 0x1e)
		alc_write_coef_idx(codec, 0x25, initval->value_0x25);

	snd_hda_codec_write(codec, 0x20, 0, AC_VERB_SET_COEF_INDEX, 0x26);
	snd_hda_codec_write(codec, 0x20, 0, AC_VERB_SET_PROC_COEF, 0xb010);
}