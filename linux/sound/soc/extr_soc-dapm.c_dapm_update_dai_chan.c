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
struct snd_soc_dapm_widget {int id; int channel; TYPE_1__* dapm; } ;
struct snd_soc_dapm_path {TYPE_3__* sink; TYPE_2__* source; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  snd_soc_dapm_aif_in 129 
#define  snd_soc_dapm_aif_out 128 
 int /*<<< orphan*/  soc_dapm_connect_path (struct snd_soc_dapm_path*,int,char*) ; 

__attribute__((used)) static int dapm_update_dai_chan(struct snd_soc_dapm_path *p,
				struct snd_soc_dapm_widget *w,
				int channels)
{
	switch (w->id) {
	case snd_soc_dapm_aif_out:
	case snd_soc_dapm_aif_in:
		break;
	default:
		return 0;
	}

	dev_dbg(w->dapm->dev, "%s DAI route %s -> %s\n",
		w->channel < channels ? "Connecting" : "Disconnecting",
		p->source->name, p->sink->name);

	if (w->channel < channels)
		soc_dapm_connect_path(p, true, "dai update");
	else
		soc_dapm_connect_path(p, false, "dai update");

	return 0;
}