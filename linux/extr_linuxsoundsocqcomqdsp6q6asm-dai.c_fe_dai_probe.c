#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afe_pcm_routes ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fe_dai_probe(struct snd_soc_dai *dai)
{
	struct snd_soc_dapm_context *dapm;

	dapm = snd_soc_component_get_dapm(dai->component);
	snd_soc_dapm_add_routes(dapm, afe_pcm_routes,
				ARRAY_SIZE(afe_pcm_routes));

	return 0;
}