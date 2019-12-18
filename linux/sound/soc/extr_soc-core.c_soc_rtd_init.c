#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int dev_registered; TYPE_2__* card; TYPE_3__* dev; TYPE_1__* dpcm; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  fe_clients; int /*<<< orphan*/  be_clients; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct snd_soc_pcm_runtime*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,char const*) ; 
 int device_register (TYPE_3__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  soc_dev_attr_groups ; 
 int /*<<< orphan*/  soc_rtd_release ; 

__attribute__((used)) static int soc_rtd_init(struct snd_soc_pcm_runtime *rtd, const char *name)
{
	int ret = 0;

	/* register the rtd device */
	rtd->dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!rtd->dev)
		return -ENOMEM;
	rtd->dev->parent = rtd->card->dev;
	rtd->dev->release = soc_rtd_release;
	rtd->dev->groups = soc_dev_attr_groups;
	dev_set_name(rtd->dev, "%s", name);
	dev_set_drvdata(rtd->dev, rtd);
	INIT_LIST_HEAD(&rtd->dpcm[SNDRV_PCM_STREAM_PLAYBACK].be_clients);
	INIT_LIST_HEAD(&rtd->dpcm[SNDRV_PCM_STREAM_CAPTURE].be_clients);
	INIT_LIST_HEAD(&rtd->dpcm[SNDRV_PCM_STREAM_PLAYBACK].fe_clients);
	INIT_LIST_HEAD(&rtd->dpcm[SNDRV_PCM_STREAM_CAPTURE].fe_clients);
	ret = device_register(rtd->dev);
	if (ret < 0) {
		/* calling put_device() here to free the rtd->dev */
		put_device(rtd->dev);
		dev_err(rtd->card->dev,
			"ASoC: failed to register runtime device: %d\n", ret);
		return ret;
	}
	rtd->dev_registered = 1;
	return 0;
}