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
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {unsigned char* status; } ;
struct TYPE_7__ {TYPE_2__ iec958; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct rpi_cirrus_priv {unsigned char* iec958_status; } ;
struct TYPE_8__ {TYPE_1__* codec_dai; } ;
struct TYPE_5__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 scalar_t__ WM8804_SPDTX1 ; 
 TYPE_4__* get_wm8804_runtime (struct snd_soc_card*) ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,scalar_t__,unsigned int,unsigned char) ; 

__attribute__((used)) static int rpi_cirrus_spdif_playback_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_component *wm8804_component =
		get_wm8804_runtime(card)->codec_dai->component;
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	unsigned char *stat = priv->iec958_status;
	unsigned char *ctrl_stat = ucontrol->value.iec958.status;
	unsigned int mask;
	int i, changed = 0;

	for (i = 0; i < 4; i++) {
		mask = (i == 3) ? 0x3f : 0xff;
		if ((ctrl_stat[i] & mask) != (stat[i] & mask)) {
			changed = 1;
			stat[i] = ctrl_stat[i] & mask;
			snd_soc_component_update_bits(wm8804_component,
				WM8804_SPDTX1 + i, mask, stat[i]);
		}
	}

	return changed;
}