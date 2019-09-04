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
struct snd_soc_dai_link_component {int /*<<< orphan*/  dai_name; int /*<<< orphan*/  of_node; } ;
struct snd_soc_dai_link {int num_codecs; struct snd_soc_dai_link_component* codecs; } ;
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct snd_soc_dai_link_component* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int snd_soc_get_dai_name (struct of_phandle_args*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_of_put_dai_link_codecs (struct snd_soc_dai_link*) ; 

int snd_soc_of_get_dai_link_codecs(struct device *dev,
				   struct device_node *of_node,
				   struct snd_soc_dai_link *dai_link)
{
	struct of_phandle_args args;
	struct snd_soc_dai_link_component *component;
	char *name;
	int index, num_codecs, ret;

	/* Count the number of CODECs */
	name = "sound-dai";
	num_codecs = of_count_phandle_with_args(of_node, name,
						"#sound-dai-cells");
	if (num_codecs <= 0) {
		if (num_codecs == -ENOENT)
			dev_err(dev, "No 'sound-dai' property\n");
		else
			dev_err(dev, "Bad phandle in 'sound-dai'\n");
		return num_codecs;
	}
	component = devm_kcalloc(dev,
				 num_codecs, sizeof(*component),
				 GFP_KERNEL);
	if (!component)
		return -ENOMEM;
	dai_link->codecs = component;
	dai_link->num_codecs = num_codecs;

	/* Parse the list */
	for (index = 0, component = dai_link->codecs;
	     index < dai_link->num_codecs;
	     index++, component++) {
		ret = of_parse_phandle_with_args(of_node, name,
						 "#sound-dai-cells",
						  index, &args);
		if (ret)
			goto err;
		component->of_node = args.np;
		ret = snd_soc_get_dai_name(&args, &component->dai_name);
		if (ret < 0)
			goto err;
	}
	return 0;
err:
	snd_soc_of_put_dai_link_codecs(dai_link);
	dai_link->codecs = NULL;
	dai_link->num_codecs = 0;
	return ret;
}