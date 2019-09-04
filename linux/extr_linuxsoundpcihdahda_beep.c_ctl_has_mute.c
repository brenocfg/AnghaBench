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
struct snd_kcontrol {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int AC_AMPCAP_MUTE ; 
 int /*<<< orphan*/  get_amp_direction (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  get_amp_nid (struct snd_kcontrol*) ; 
 int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static bool ctl_has_mute(struct snd_kcontrol *kcontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	return query_amp_caps(codec, get_amp_nid(kcontrol),
			      get_amp_direction(kcontrol)) & AC_AMPCAP_MUTE;
}