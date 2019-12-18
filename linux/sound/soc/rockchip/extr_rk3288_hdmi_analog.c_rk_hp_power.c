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
struct snd_soc_dapm_widget {TYPE_1__* dapm; } ;
struct snd_kcontrol {int dummy; } ;
struct rk_drvdata {int /*<<< orphan*/  gpio_hp_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rk_drvdata* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk_hp_power(struct snd_soc_dapm_widget *w,
		       struct snd_kcontrol *k, int event)
{
	struct rk_drvdata *machine = snd_soc_card_get_drvdata(w->dapm->card);

	if (!gpio_is_valid(machine->gpio_hp_en))
		return 0;

	gpio_set_value_cansleep(machine->gpio_hp_en,
				SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}