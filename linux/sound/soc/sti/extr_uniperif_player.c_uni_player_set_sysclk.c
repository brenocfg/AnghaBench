#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uniperif {unsigned int mclk; int /*<<< orphan*/  ctrl_lock; } ;
struct TYPE_2__ {struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_1__ dai_data; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_CLOCK_IN ; 
 scalar_t__ UNIPERIF_TYPE_IS_TDM (struct uniperif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sti_uniperiph_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int uni_player_clk_set_rate (struct uniperif*,unsigned int) ; 

__attribute__((used)) static int uni_player_set_sysclk(struct snd_soc_dai *dai, int clk_id,
				 unsigned int freq, int dir)
{
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *player = priv->dai_data.uni;
	int ret;

	if (UNIPERIF_TYPE_IS_TDM(player) || (dir == SND_SOC_CLOCK_IN))
		return 0;

	if (clk_id != 0)
		return -EINVAL;

	mutex_lock(&player->ctrl_lock);
	ret = uni_player_clk_set_rate(player, freq);
	if (!ret)
		player->mclk = freq;
	mutex_unlock(&player->ctrl_lock);

	return ret;
}