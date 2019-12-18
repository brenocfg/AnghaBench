#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct snd_ac97 {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const* const) ; 
 struct snd_kcontrol* snd_ac97_find_mixer_ctl (struct snd_ac97*,char const* const) ; 
 int snd_ctl_add (TYPE_2__*,struct snd_kcontrol*) ; 
 int snd_ctl_add_slave (struct snd_kcontrol*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_make_virtual_master (char*,unsigned int const*) ; 

__attribute__((used)) static int snd_ac97_add_vmaster(struct snd_ac97 *ac97, char *name,
				const unsigned int *tlv,
				const char * const *slaves)
{
	struct snd_kcontrol *kctl;
	const char * const *s;
	int err;

	kctl = snd_ctl_make_virtual_master(name, tlv);
	if (!kctl)
		return -ENOMEM;
	err = snd_ctl_add(ac97->bus->card, kctl);
	if (err < 0)
		return err;

	for (s = slaves; *s; s++) {
		struct snd_kcontrol *sctl;

		sctl = snd_ac97_find_mixer_ctl(ac97, *s);
		if (!sctl) {
			dev_dbg(ac97->bus->card->dev,
				"Cannot find slave %s, skipped\n", *s);
			continue;
		}
		err = snd_ctl_add_slave(kctl, sctl);
		if (err < 0)
			return err;
	}
	return 0;
}