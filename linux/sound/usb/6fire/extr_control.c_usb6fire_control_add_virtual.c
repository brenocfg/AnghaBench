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
struct snd_kcontrol_new {scalar_t__ name; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct control_runtime {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 int snd_ctl_add_slave (struct snd_kcontrol*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_make_virtual_master (char*,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct control_runtime*) ; 
 int /*<<< orphan*/  tlv_output ; 

__attribute__((used)) static int usb6fire_control_add_virtual(
	struct control_runtime *rt,
	struct snd_card *card,
	char *name,
	struct snd_kcontrol_new *elems)
{
	int ret;
	int i;
	struct snd_kcontrol *vmaster =
		snd_ctl_make_virtual_master(name, tlv_output);
	struct snd_kcontrol *control;

	if (!vmaster)
		return -ENOMEM;
	ret = snd_ctl_add(card, vmaster);
	if (ret < 0)
		return ret;

	i = 0;
	while (elems[i].name) {
		control = snd_ctl_new1(&elems[i], rt);
		if (!control)
			return -ENOMEM;
		ret = snd_ctl_add(card, control);
		if (ret < 0)
			return ret;
		ret = snd_ctl_add_slave(vmaster, control);
		if (ret < 0)
			return ret;
		i++;
	}
	return 0;
}