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
struct snd_kcontrol_new {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_soc_cnew (struct snd_kcontrol_new const*,void*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int soc_tplg_add_dcontrol(struct snd_card *card, struct device *dev,
	const struct snd_kcontrol_new *control_new, const char *prefix,
	void *data, struct snd_kcontrol **kcontrol)
{
	int err;

	*kcontrol = snd_soc_cnew(control_new, data, control_new->name, prefix);
	if (*kcontrol == NULL) {
		dev_err(dev, "ASoC: Failed to create new kcontrol %s\n",
		control_new->name);
		return -ENOMEM;
	}

	err = snd_ctl_add(card, *kcontrol);
	if (err < 0) {
		dev_err(dev, "ASoC: Failed to add %s: %d\n",
			control_new->name, err);
		return err;
	}

	return 0;
}