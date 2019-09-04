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
struct snd_soc_pcm_runtime {size_t num; TYPE_1__* cpu_dai; int /*<<< orphan*/  card; } ;
struct axg_dai_link_tdm_data {int /*<<< orphan*/  slot_width; int /*<<< orphan*/  slots; int /*<<< orphan*/  tx_mask; } ;
struct axg_card {scalar_t__* link_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int axg_tdm_set_tdm_slots (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct axg_card* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_card_tdm_dai_lb_init(struct snd_soc_pcm_runtime *rtd)
{
	struct axg_card *priv = snd_soc_card_get_drvdata(rtd->card);
	struct axg_dai_link_tdm_data *be =
		(struct axg_dai_link_tdm_data *)priv->link_data[rtd->num];
	int ret;

	/* The loopback rx_mask is the pad tx_mask */
	ret = axg_tdm_set_tdm_slots(rtd->cpu_dai, NULL, be->tx_mask,
				    be->slots, be->slot_width);
	if (ret) {
		dev_err(rtd->cpu_dai->dev, "setting tdm link slots failed\n");
		return ret;
	}

	return 0;
}