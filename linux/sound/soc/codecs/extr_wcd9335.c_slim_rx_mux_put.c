#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct wcd9335_codec {int rx_port_value; int /*<<< orphan*/  dev; TYPE_4__* dai; TYPE_3__* rx_chs; } ;
struct soc_enum {int dummy; } ;
struct snd_soc_dapm_widget {size_t shift; TYPE_5__* dapm; } ;
struct snd_soc_dapm_update {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_6__ {int* item; } ;
struct TYPE_7__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  slim_ch_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 size_t AIF1_PB ; 
 size_t AIF2_PB ; 
 size_t AIF3_PB ; 
 size_t AIF4_PB ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_widget* snd_soc_dapm_kcontrol_widget (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mux_update_power (TYPE_5__*,struct snd_kcontrol*,int,struct soc_enum*,struct snd_soc_dapm_update*) ; 

__attribute__((used)) static int slim_rx_mux_put(struct snd_kcontrol *kc,
			   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kc);
	struct wcd9335_codec *wcd = dev_get_drvdata(w->dapm->dev);
	struct soc_enum *e = (struct soc_enum *)kc->private_value;
	struct snd_soc_dapm_update *update = NULL;
	u32 port_id = w->shift;

	wcd->rx_port_value = ucontrol->value.enumerated.item[0];

	switch (wcd->rx_port_value) {
	case 0:
		list_del_init(&wcd->rx_chs[port_id].list);
		break;
	case 1:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF1_PB].slim_ch_list);
		break;
	case 2:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF2_PB].slim_ch_list);
		break;
	case 3:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF3_PB].slim_ch_list);
		break;
	case 4:
		list_add_tail(&wcd->rx_chs[port_id].list,
			      &wcd->dai[AIF4_PB].slim_ch_list);
		break;
	default:
		dev_err(wcd->dev, "Unknown AIF %d\n", wcd->rx_port_value);
		goto err;
	}

	snd_soc_dapm_mux_update_power(w->dapm, kc, wcd->rx_port_value,
				      e, update);

	return 0;
err:
	return -EINVAL;
}