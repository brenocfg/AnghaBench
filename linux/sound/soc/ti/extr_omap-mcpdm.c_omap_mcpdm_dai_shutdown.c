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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int stream; } ;
struct omap_mcpdm {int /*<<< orphan*/  mutex; scalar_t__* latency; int /*<<< orphan*/  pm_qos_req; TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ link_mask; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ omap_mcpdm_active (struct omap_mcpdm*) ; 
 int /*<<< orphan*/  omap_mcpdm_close_streams (struct omap_mcpdm*) ; 
 int /*<<< orphan*/  omap_mcpdm_stop (struct omap_mcpdm*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,scalar_t__) ; 
 struct omap_mcpdm* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void omap_mcpdm_dai_shutdown(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);
	int tx = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	int stream1 = tx ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	int stream2 = tx ? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;

	mutex_lock(&mcpdm->mutex);

	if (!dai->active) {
		if (omap_mcpdm_active(mcpdm)) {
			omap_mcpdm_stop(mcpdm);
			omap_mcpdm_close_streams(mcpdm);
			mcpdm->config[0].link_mask = 0;
			mcpdm->config[1].link_mask = 0;
		}
	}

	if (mcpdm->latency[stream2])
		pm_qos_update_request(&mcpdm->pm_qos_req,
				      mcpdm->latency[stream2]);
	else if (mcpdm->latency[stream1])
		pm_qos_remove_request(&mcpdm->pm_qos_req);

	mcpdm->latency[stream1] = 0;

	mutex_unlock(&mcpdm->mutex);
}