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
struct snd_soc_dapm_route {char* control; int /*<<< orphan*/  sink; int /*<<< orphan*/  source; } ;
struct snd_soc_dapm_context {TYPE_1__* card; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dapm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_CLASS_RUNTIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_soc_dapm_add_route (struct snd_soc_dapm_context*,struct snd_soc_dapm_route const*) ; 

int snd_soc_dapm_add_routes(struct snd_soc_dapm_context *dapm,
			    const struct snd_soc_dapm_route *route, int num)
{
	int i, r, ret = 0;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	for (i = 0; i < num; i++) {
		r = snd_soc_dapm_add_route(dapm, route);
		if (r < 0) {
			dev_err(dapm->dev, "ASoC: Failed to add route %s -> %s -> %s\n",
				route->source,
				route->control ? route->control : "direct",
				route->sink);
			ret = r;
		}
		route++;
	}
	mutex_unlock(&dapm->card->dapm_mutex);

	return ret;
}