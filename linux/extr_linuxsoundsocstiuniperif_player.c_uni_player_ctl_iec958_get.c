#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_aes_iec958 {int /*<<< orphan*/ * status; } ;
struct TYPE_6__ {struct snd_aes_iec958 iec958; } ;
struct uniperif {int /*<<< orphan*/  ctrl_lock; TYPE_2__ stream_settings; } ;
struct TYPE_5__ {struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_1__ dai_data; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * status; } ;
struct TYPE_8__ {TYPE_3__ iec958; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct sti_uniperiph_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int uni_player_ctl_iec958_get(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *player = priv->dai_data.uni;
	struct snd_aes_iec958 *iec958 = &player->stream_settings.iec958;

	mutex_lock(&player->ctrl_lock);
	ucontrol->value.iec958.status[0] = iec958->status[0];
	ucontrol->value.iec958.status[1] = iec958->status[1];
	ucontrol->value.iec958.status[2] = iec958->status[2];
	ucontrol->value.iec958.status[3] = iec958->status[3];
	mutex_unlock(&player->ctrl_lock);
	return 0;
}