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
struct snd_kcontrol_new {int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct snd_kcontrol_new HDA_CODEC_MUTE_MONO (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  MIC_BOOST_ENUM ; 
 int /*<<< orphan*/  ca0132_alt_mic_boost_get ; 
 int /*<<< orphan*/  ca0132_alt_mic_boost_info ; 
 int /*<<< orphan*/  ca0132_alt_mic_boost_put ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct hda_codec*) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca0132_alt_add_mic_boost_enum(struct hda_codec *codec)
{
	struct snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("Mic Boost Capture Switch",
				    MIC_BOOST_ENUM, 1, 0, HDA_INPUT);
	knew.info = ca0132_alt_mic_boost_info;
	knew.get = ca0132_alt_mic_boost_get;
	knew.put = ca0132_alt_mic_boost_put;
	return snd_hda_ctl_add(codec, MIC_BOOST_ENUM,
				snd_ctl_new1(&knew, codec));

}