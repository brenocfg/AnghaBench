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
struct slave_init_arg {int /*<<< orphan*/  step; struct hda_codec* codec; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  add_slave ; 
 int /*<<< orphan*/  check_slave_present ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,char*) ; 
 int /*<<< orphan*/  init_slave_0dB ; 
 int /*<<< orphan*/  init_slave_unmute ; 
 int map_slaves (struct hda_codec*,char const* const*,char const*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  put_kctl_with_value (struct snd_kcontrol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_apply_vmaster_slaves (struct snd_kcontrol*,int /*<<< orphan*/ ,struct slave_init_arg*) ; 
 struct snd_kcontrol* snd_ctl_make_virtual_master (char*,unsigned int*) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 

int __snd_hda_add_vmaster(struct hda_codec *codec, char *name,
			unsigned int *tlv, const char * const *slaves,
			  const char *suffix, bool init_slave_vol,
			  struct snd_kcontrol **ctl_ret)
{
	struct snd_kcontrol *kctl;
	int err;

	if (ctl_ret)
		*ctl_ret = NULL;

	err = map_slaves(codec, slaves, suffix, check_slave_present, NULL);
	if (err != 1) {
		codec_dbg(codec, "No slave found for %s\n", name);
		return 0;
	}
	kctl = snd_ctl_make_virtual_master(name, tlv);
	if (!kctl)
		return -ENOMEM;
	err = snd_hda_ctl_add(codec, 0, kctl);
	if (err < 0)
		return err;

	err = map_slaves(codec, slaves, suffix, add_slave, kctl);
	if (err < 0)
		return err;

	/* init with master mute & zero volume */
	put_kctl_with_value(kctl, 0);
	if (init_slave_vol) {
		struct slave_init_arg arg = {
			.codec = codec,
			.step = 0,
		};
		snd_ctl_apply_vmaster_slaves(kctl,
					     tlv ? init_slave_0dB : init_slave_unmute,
					     &arg);
	}

	if (ctl_ret)
		*ctl_ret = kctl;
	return 0;
}