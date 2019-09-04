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
struct nau8824 {struct snd_soc_dapm_context* dapm; } ;

/* Variables and functions */
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct nau8824* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8824_component_probe(struct snd_soc_component *component)
{
	struct nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	nau8824->dapm = dapm;

	return 0;
}