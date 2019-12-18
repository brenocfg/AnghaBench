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
struct sst_pdata {int /*<<< orphan*/  dsp; } ;
struct sst_byt_priv_data {TYPE_1__* pcm; int /*<<< orphan*/  byt; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int BYT_PCM_COUNT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sst_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct sst_byt_priv_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct sst_byt_priv_data*) ; 
 int /*<<< orphan*/  sst_byt_pcm_work ; 

__attribute__((used)) static int sst_byt_pcm_probe(struct snd_soc_component *component)
{
	struct sst_pdata *plat_data = dev_get_platdata(component->dev);
	struct sst_byt_priv_data *priv_data;
	int i;

	if (!plat_data)
		return -ENODEV;

	priv_data = devm_kzalloc(component->dev, sizeof(*priv_data),
				 GFP_KERNEL);
	if (!priv_data)
		return -ENOMEM;
	priv_data->byt = plat_data->dsp;
	snd_soc_component_set_drvdata(component, priv_data);

	for (i = 0; i < BYT_PCM_COUNT; i++) {
		mutex_init(&priv_data->pcm[i].mutex);
		INIT_WORK(&priv_data->pcm[i].work, sst_byt_pcm_work);
	}

	return 0;
}