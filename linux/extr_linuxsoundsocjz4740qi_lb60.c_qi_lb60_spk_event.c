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
struct qi_lb60 {int /*<<< orphan*/  amp_gpio; int /*<<< orphan*/  snd_gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_EVENT_OFF (int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct qi_lb60* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qi_lb60_spk_event(struct snd_soc_dapm_widget *widget,
			     struct snd_kcontrol *ctrl, int event)
{
	struct qi_lb60 *qi_lb60 = snd_soc_card_get_drvdata(widget->dapm->card);
	int on = !SND_SOC_DAPM_EVENT_OFF(event);

	gpiod_set_value_cansleep(qi_lb60->snd_gpio, on);
	gpiod_set_value_cansleep(qi_lb60->amp_gpio, on);

	return 0;
}