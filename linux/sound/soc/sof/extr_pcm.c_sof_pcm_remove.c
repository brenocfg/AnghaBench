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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_TPLG_INDEX_ALL ; 
 int /*<<< orphan*/  snd_soc_tplg_component_remove (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sof_pcm_remove(struct snd_soc_component *component)
{
	/* remove topology */
	snd_soc_tplg_component_remove(component, SND_SOC_TPLG_INDEX_ALL);
}