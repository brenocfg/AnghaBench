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
struct snd_soc_dai_link {int /*<<< orphan*/  cpu_of_node; int /*<<< orphan*/  cpu_dai_name; } ;
struct snd_soc_card {struct snd_soc_dai_link* dai_link; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ axg_card_cpu_is_capture_fe (int /*<<< orphan*/ ) ; 
 scalar_t__ axg_card_cpu_is_playback_fe (int /*<<< orphan*/ ) ; 
 scalar_t__ axg_card_cpu_is_tdm_iface (int /*<<< orphan*/ ) ; 
 int axg_card_parse_dai (struct snd_soc_card*,struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int axg_card_parse_tdm (struct snd_soc_card*,struct device_node*,int*) ; 
 int axg_card_set_be_link (struct snd_soc_card*,struct snd_soc_dai_link*,struct device_node*) ; 
 int axg_card_set_fe_link (struct snd_soc_card*,struct snd_soc_dai_link*,int) ; 

__attribute__((used)) static int axg_card_add_link(struct snd_soc_card *card, struct device_node *np,
			     int *index)
{
	struct snd_soc_dai_link *dai_link = &card->dai_link[*index];
	int ret;

	ret = axg_card_parse_dai(card, np, &dai_link->cpu_of_node,
				 &dai_link->cpu_dai_name);
	if (ret)
		return ret;

	if (axg_card_cpu_is_playback_fe(dai_link->cpu_of_node))
		ret = axg_card_set_fe_link(card, dai_link, true);
	else if (axg_card_cpu_is_capture_fe(dai_link->cpu_of_node))
		ret = axg_card_set_fe_link(card, dai_link, false);
	else
		ret = axg_card_set_be_link(card, dai_link, np);

	if (ret)
		return ret;

	if (axg_card_cpu_is_tdm_iface(dai_link->cpu_of_node))
		ret = axg_card_parse_tdm(card, np, index);

	return ret;
}