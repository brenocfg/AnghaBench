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
struct TYPE_6__ {int reg_mask; scalar_t__ reg; } ;
struct snd_pcm {int info_flags; char* name; TYPE_3__ oss; scalar_t__ device; TYPE_2__* card; TYPE_1__* streams; } ;
struct TYPE_5__ {size_t number; } ;
struct TYPE_4__ {scalar_t__ substream_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_OSS_INFO_DEV_AUDIO ; 
 int SNDRV_PCM_INFO_HALF_DUPLEX ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int* adsp_map ; 
 int* dsp_map ; 
 int /*<<< orphan*/  register_oss_dsp (struct snd_pcm*,int) ; 
 int /*<<< orphan*/  snd_oss_info_register (int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  snd_pcm_oss_proc_init (struct snd_pcm*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static int snd_pcm_oss_register_minor(struct snd_pcm *pcm)
{
	pcm->oss.reg = 0;
	if (dsp_map[pcm->card->number] == (int)pcm->device) {
		char name[128];
		int duplex;
		register_oss_dsp(pcm, 0);
		duplex = (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream_count > 0 && 
			      pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream_count && 
			      !(pcm->info_flags & SNDRV_PCM_INFO_HALF_DUPLEX));
		sprintf(name, "%s%s", pcm->name, duplex ? " (DUPLEX)" : "");
#ifdef SNDRV_OSS_INFO_DEV_AUDIO
		snd_oss_info_register(SNDRV_OSS_INFO_DEV_AUDIO,
				      pcm->card->number,
				      name);
#endif
		pcm->oss.reg++;
		pcm->oss.reg_mask |= 1;
	}
	if (adsp_map[pcm->card->number] == (int)pcm->device) {
		register_oss_dsp(pcm, 1);
		pcm->oss.reg++;
		pcm->oss.reg_mask |= 2;
	}

	if (pcm->oss.reg)
		snd_pcm_oss_proc_init(pcm);

	return 0;
}