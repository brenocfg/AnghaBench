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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int stream; } ;
struct omap_mcbsp {scalar_t__ configured; scalar_t__* latency; int /*<<< orphan*/  pm_qos_req; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  omap_mcbsp_free (struct omap_mcbsp*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,scalar_t__) ; 
 struct omap_mcbsp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void omap_mcbsp_dai_shutdown(struct snd_pcm_substream *substream,
				    struct snd_soc_dai *cpu_dai)
{
	struct omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	int tx = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	int stream1 = tx ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	int stream2 = tx ? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;

	if (mcbsp->latency[stream2])
		pm_qos_update_request(&mcbsp->pm_qos_req,
				      mcbsp->latency[stream2]);
	else if (mcbsp->latency[stream1])
		pm_qos_remove_request(&mcbsp->pm_qos_req);

	mcbsp->latency[stream1] = 0;

	if (!cpu_dai->active) {
		omap_mcbsp_free(mcbsp);
		mcbsp->configured = 0;
	}
}