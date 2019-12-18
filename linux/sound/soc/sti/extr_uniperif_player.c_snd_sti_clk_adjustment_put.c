#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uniperif {scalar_t__ clk_adj; int /*<<< orphan*/  ctrl_lock; scalar_t__ mclk; } ;
struct TYPE_4__ {struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_1__ dai_data; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNIPERIF_PLAYER_CLK_ADJ_MAX ; 
 scalar_t__ UNIPERIF_PLAYER_CLK_ADJ_MIN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct sti_uniperiph_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int uni_player_clk_set_rate (struct uniperif*,scalar_t__) ; 

__attribute__((used)) static int snd_sti_clk_adjustment_put(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *player = priv->dai_data.uni;
	int ret = 0;

	if ((ucontrol->value.integer.value[0] < UNIPERIF_PLAYER_CLK_ADJ_MIN) ||
	    (ucontrol->value.integer.value[0] > UNIPERIF_PLAYER_CLK_ADJ_MAX))
		return -EINVAL;

	mutex_lock(&player->ctrl_lock);
	player->clk_adj = ucontrol->value.integer.value[0];

	if (player->mclk)
		ret = uni_player_clk_set_rate(player, player->mclk);
	mutex_unlock(&player->ctrl_lock);

	return ret;
}