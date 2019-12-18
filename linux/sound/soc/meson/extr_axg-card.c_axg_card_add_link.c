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
struct snd_soc_dai_link_component {int /*<<< orphan*/  of_node; int /*<<< orphan*/  dai_name; } ;
struct snd_soc_dai_link {int num_cpus; int /*<<< orphan*/ * params; struct snd_soc_dai_link_component* cpus; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; struct snd_soc_dai_link* dai_link; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ axg_card_cpu_is_capture_fe (int /*<<< orphan*/ ) ; 
 scalar_t__ axg_card_cpu_is_codec (int /*<<< orphan*/ ) ; 
 scalar_t__ axg_card_cpu_is_playback_fe (int /*<<< orphan*/ ) ; 
 scalar_t__ axg_card_cpu_is_tdm_iface (int /*<<< orphan*/ ) ; 
 int axg_card_parse_dai (struct snd_soc_card*,struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int axg_card_parse_tdm (struct snd_soc_card*,struct device_node*,int*) ; 
 int axg_card_set_be_link (struct snd_soc_card*,struct snd_soc_dai_link*,struct device_node*) ; 
 int axg_card_set_fe_link (struct snd_soc_card*,struct snd_soc_dai_link*,struct device_node*,int) ; 
 int /*<<< orphan*/  codec_params ; 
 struct snd_soc_dai_link_component* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_card_add_link(struct snd_soc_card *card, struct device_node *np,
			     int *index)
{
	struct snd_soc_dai_link *dai_link = &card->dai_link[*index];
	struct snd_soc_dai_link_component *cpu;
	int ret;

	cpu = devm_kzalloc(card->dev, sizeof(*cpu), GFP_KERNEL);
	if (!cpu)
		return -ENOMEM;

	dai_link->cpus = cpu;
	dai_link->num_cpus = 1;

	ret = axg_card_parse_dai(card, np, &dai_link->cpus->of_node,
				 &dai_link->cpus->dai_name);
	if (ret)
		return ret;

	if (axg_card_cpu_is_playback_fe(dai_link->cpus->of_node))
		ret = axg_card_set_fe_link(card, dai_link, np, true);
	else if (axg_card_cpu_is_capture_fe(dai_link->cpus->of_node))
		ret = axg_card_set_fe_link(card, dai_link, np, false);
	else
		ret = axg_card_set_be_link(card, dai_link, np);

	if (ret)
		return ret;

	if (axg_card_cpu_is_tdm_iface(dai_link->cpus->of_node))
		ret = axg_card_parse_tdm(card, np, index);
	else if (axg_card_cpu_is_codec(dai_link->cpus->of_node))
		dai_link->params = &codec_params;

	return ret;
}