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
struct snd_soc_card {unsigned int num_controls; struct snd_kcontrol_new* controls; struct device* dev; } ;
struct snd_kcontrol_new {char const* name; unsigned long private_value; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  iface; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  prop ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,char const*) ; 
 void* devm_kcalloc (struct device*,unsigned int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_string_array (int /*<<< orphan*/ ,char*,char const**,unsigned int const) ; 
 int /*<<< orphan*/  snd_soc_dapm_get_pin_switch ; 
 int /*<<< orphan*/  snd_soc_dapm_info_pin_switch ; 
 int /*<<< orphan*/  snd_soc_dapm_put_pin_switch ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

int asoc_simple_parse_pin_switches(struct snd_soc_card *card,
				   char *prefix)
{
	const unsigned int nb_controls_max = 16;
	const char **strings, *control_name;
	struct snd_kcontrol_new *controls;
	struct device *dev = card->dev;
	unsigned int i, nb_controls;
	char prop[128];
	int ret;

	if (!prefix)
		prefix = "";

	snprintf(prop, sizeof(prop), "%s%s", prefix, "pin-switches");

	if (!of_property_read_bool(dev->of_node, prop))
		return 0;

	strings = devm_kcalloc(dev, nb_controls_max,
			       sizeof(*strings), GFP_KERNEL);
	if (!strings)
		return -ENOMEM;

	ret = of_property_read_string_array(dev->of_node, prop,
					    strings, nb_controls_max);
	if (ret < 0)
		return ret;

	nb_controls = (unsigned int)ret;

	controls = devm_kcalloc(dev, nb_controls,
				sizeof(*controls), GFP_KERNEL);
	if (!controls)
		return -ENOMEM;

	for (i = 0; i < nb_controls; i++) {
		control_name = devm_kasprintf(dev, GFP_KERNEL,
					      "%s Switch", strings[i]);
		if (!control_name)
			return -ENOMEM;

		controls[i].iface = SNDRV_CTL_ELEM_IFACE_MIXER;
		controls[i].name = control_name;
		controls[i].info = snd_soc_dapm_info_pin_switch;
		controls[i].get = snd_soc_dapm_get_pin_switch;
		controls[i].put = snd_soc_dapm_put_pin_switch;
		controls[i].private_value = (unsigned long)strings[i];
	}

	card->controls = controls;
	card->num_controls = nb_controls;

	return 0;
}