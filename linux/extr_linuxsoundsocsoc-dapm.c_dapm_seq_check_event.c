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
struct snd_soc_dapm_widget {int new_power; int (* event ) (struct snd_soc_dapm_widget*,int /*<<< orphan*/ *,int) ;int event_flags; int /*<<< orphan*/  name; TYPE_1__* dapm; } ;
struct snd_soc_card {int /*<<< orphan*/  pop_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 133 
#define  SND_SOC_DAPM_POST_PMU 132 
#define  SND_SOC_DAPM_PRE_PMD 131 
#define  SND_SOC_DAPM_PRE_PMU 130 
#define  SND_SOC_DAPM_WILL_PMD 129 
#define  SND_SOC_DAPM_WILL_PMU 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pop_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  soc_dapm_async_complete (TYPE_1__*) ; 
 int stub1 (struct snd_soc_dapm_widget*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_snd_soc_dapm_widget_event_done (struct snd_soc_dapm_widget*,int) ; 
 int /*<<< orphan*/  trace_snd_soc_dapm_widget_event_start (struct snd_soc_dapm_widget*,int) ; 

__attribute__((used)) static void dapm_seq_check_event(struct snd_soc_card *card,
				 struct snd_soc_dapm_widget *w, int event)
{
	const char *ev_name;
	int power, ret;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		ev_name = "PRE_PMU";
		power = 1;
		break;
	case SND_SOC_DAPM_POST_PMU:
		ev_name = "POST_PMU";
		power = 1;
		break;
	case SND_SOC_DAPM_PRE_PMD:
		ev_name = "PRE_PMD";
		power = 0;
		break;
	case SND_SOC_DAPM_POST_PMD:
		ev_name = "POST_PMD";
		power = 0;
		break;
	case SND_SOC_DAPM_WILL_PMU:
		ev_name = "WILL_PMU";
		power = 1;
		break;
	case SND_SOC_DAPM_WILL_PMD:
		ev_name = "WILL_PMD";
		power = 0;
		break;
	default:
		WARN(1, "Unknown event %d\n", event);
		return;
	}

	if (w->new_power != power)
		return;

	if (w->event && (w->event_flags & event)) {
		pop_dbg(w->dapm->dev, card->pop_time, "pop test : %s %s\n",
			w->name, ev_name);
		soc_dapm_async_complete(w->dapm);
		trace_snd_soc_dapm_widget_event_start(w, event);
		ret = w->event(w, NULL, event);
		trace_snd_soc_dapm_widget_event_done(w, event);
		if (ret < 0)
			dev_err(w->dapm->dev, "ASoC: %s: %s event failed: %d\n",
			       ev_name, w->name, ret);
	}
}