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
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; TYPE_1__* card; } ;
struct snd_pcm {int dummy; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_5__ {int /*<<< orphan*/  tasklet; } ;
struct siu_port {TYPE_3__ capture; TYPE_2__ playback; struct snd_pcm* pcm; } ;
struct siu_info {int port_id; } ;
struct platform_device {int id; } ;
struct TYPE_4__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SIU_BUFFER_BYTES_MAX ; 
 int SIU_PORT_NUM ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct siu_info* siu_i2s_data ; 
 int siu_init_port (int,struct siu_port**,struct snd_card*) ; 
 int /*<<< orphan*/  siu_io_tasklet ; 
 struct siu_port** siu_ports ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siu_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	/* card->dev == socdev->dev, see snd_soc_new_pcms() */
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm *pcm = rtd->pcm;
	struct siu_info *info = siu_i2s_data;
	struct platform_device *pdev = to_platform_device(card->dev);
	int ret;
	int i;

	/* pdev->id selects between SIUA and SIUB */
	if (pdev->id < 0 || pdev->id >= SIU_PORT_NUM)
		return -EINVAL;

	info->port_id = pdev->id;

	/*
	 * While the siu has 2 ports, only one port can be on at a time (only 1
	 * SPB). So far all the boards using the siu had only one of the ports
	 * wired to a codec. To simplify things, we only register one port with
	 * alsa. In case both ports are needed, it should be changed here
	 */
	for (i = pdev->id; i < pdev->id + 1; i++) {
		struct siu_port **port_info = &siu_ports[i];

		ret = siu_init_port(i, port_info, card);
		if (ret < 0)
			return ret;

		snd_pcm_lib_preallocate_pages_for_all(pcm,
				SNDRV_DMA_TYPE_DEV, card->dev,
				SIU_BUFFER_BYTES_MAX, SIU_BUFFER_BYTES_MAX);

		(*port_info)->pcm = pcm;

		/* IO tasklets */
		tasklet_init(&(*port_info)->playback.tasklet, siu_io_tasklet,
			     (unsigned long)&(*port_info)->playback);
		tasklet_init(&(*port_info)->capture.tasklet, siu_io_tasklet,
			     (unsigned long)&(*port_info)->capture);
	}

	dev_info(card->dev, "SuperH SIU driver initialized.\n");
	return 0;
}