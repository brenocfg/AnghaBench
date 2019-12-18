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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct cs43130_private {int /*<<< orphan*/  clk_mutex; int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS43130_MCLK_SRC_RCO ; 
 int /*<<< orphan*/  cs43130_change_clksrc (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs43130_pcm_dsd_mix (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs43130_hw_free(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);

	mutex_lock(&cs43130->clk_mutex);
	cs43130->clk_req--;
	if (!cs43130->clk_req) {
		/* no DAI is currently using clk */
		cs43130_change_clksrc(component, CS43130_MCLK_SRC_RCO);
		cs43130_pcm_dsd_mix(false, cs43130->regmap);
	}
	mutex_unlock(&cs43130->clk_mutex);

	return 0;
}