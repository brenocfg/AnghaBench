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
struct snd_soc_component {int dummy; } ;
struct cs53l30_private {scalar_t__ use_sdout2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs53l30_dapm_routes_sdout1 ; 
 int /*<<< orphan*/  cs53l30_dapm_routes_sdout2 ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs53l30_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs53l30_component_probe(struct snd_soc_component *component)
{
	struct cs53l30_private *priv = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (priv->use_sdout2)
		snd_soc_dapm_add_routes(dapm, cs53l30_dapm_routes_sdout2,
					ARRAY_SIZE(cs53l30_dapm_routes_sdout2));
	else
		snd_soc_dapm_add_routes(dapm, cs53l30_dapm_routes_sdout1,
					ARRAY_SIZE(cs53l30_dapm_routes_sdout1));

	return 0;
}