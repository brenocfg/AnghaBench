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
struct snd_pcm_ops {void* open; } ;
struct snd_pcm {struct snd_cmi8330* private_data; int /*<<< orphan*/  name; } ;
struct snd_cmi8330 {scalar_t__ type; struct snd_pcm* pcm; TYPE_1__* streams; int /*<<< orphan*/  wss; int /*<<< orphan*/  sb; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
typedef  void* snd_pcm_open_callback_t ;
struct TYPE_2__ {struct snd_pcm_ops ops; int /*<<< orphan*/  private_data; void* open; } ;

/* Variables and functions */
 scalar_t__ CMI8329 ; 
 size_t CMI_AD_STREAM ; 
 size_t CMI_SB_STREAM ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
#define  snd_cmi8330_capture_open 129 
#define  snd_cmi8330_playback_open 128 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (struct snd_card*,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,struct snd_pcm_ops*) ; 
 struct snd_pcm_ops* snd_sb16dsp_get_pcm_ops (size_t) ; 
 struct snd_pcm_ops* snd_wss_get_pcm_ops (size_t) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_cmi8330_pcm(struct snd_card *card, struct snd_cmi8330 *chip)
{
	struct snd_pcm *pcm;
	const struct snd_pcm_ops *ops;
	int err;
	static snd_pcm_open_callback_t cmi_open_callbacks[2] = {
		snd_cmi8330_playback_open,
		snd_cmi8330_capture_open
	};

	if ((err = snd_pcm_new(card, (chip->type == CMI8329) ? "CMI8329" : "CMI8330", 0, 1, 1, &pcm)) < 0)
		return err;
	strcpy(pcm->name, (chip->type == CMI8329) ? "CMI8329" : "CMI8330");
	pcm->private_data = chip;
	
	/* SB16 */
	ops = snd_sb16dsp_get_pcm_ops(CMI_SB_STREAM);
	chip->streams[CMI_SB_STREAM].ops = *ops;
	chip->streams[CMI_SB_STREAM].open = ops->open;
	chip->streams[CMI_SB_STREAM].ops.open = cmi_open_callbacks[CMI_SB_STREAM];
	chip->streams[CMI_SB_STREAM].private_data = chip->sb;

	/* AD1848 */
	ops = snd_wss_get_pcm_ops(CMI_AD_STREAM);
	chip->streams[CMI_AD_STREAM].ops = *ops;
	chip->streams[CMI_AD_STREAM].open = ops->open;
	chip->streams[CMI_AD_STREAM].ops.open = cmi_open_callbacks[CMI_AD_STREAM];
	chip->streams[CMI_AD_STREAM].private_data = chip->wss;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &chip->streams[SNDRV_PCM_STREAM_PLAYBACK].ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &chip->streams[SNDRV_PCM_STREAM_CAPTURE].ops);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      card->dev,
					      64*1024, 128*1024);
	chip->pcm = pcm;

	return 0;
}