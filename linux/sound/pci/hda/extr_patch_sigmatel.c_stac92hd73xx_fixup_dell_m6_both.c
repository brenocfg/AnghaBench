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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  snd_hda_codec_set_pincfg (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  stac92hd73xx_fixup_dell (struct hda_codec*) ; 

__attribute__((used)) static void stac92hd73xx_fixup_dell_m6_both(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	stac92hd73xx_fixup_dell(codec);
	snd_hda_codec_set_pincfg(codec, 0x0b, 0x90A70170);
	snd_hda_codec_set_pincfg(codec, 0x13, 0x90A60160);
}