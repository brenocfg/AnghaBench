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
struct sst_data {int /*<<< orphan*/  soc_card; } ;
struct snd_soc_component {int /*<<< orphan*/  card; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sst_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int sst_dsp_init_v2_dpcm (struct snd_soc_component*) ; 

__attribute__((used)) static int sst_soc_probe(struct snd_soc_component *component)
{
	struct sst_data *drv = dev_get_drvdata(component->dev);

	drv->soc_card = component->card;
	return sst_dsp_init_v2_dpcm(component);
}