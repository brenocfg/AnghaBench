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
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddma_chan; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  au1xxx_dbdma_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xxx_dbdma_stop (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_dmadata (struct snd_pcm_substream*) ; 

__attribute__((used)) static int au1xpsc_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	u32 c = to_dmadata(substream)->ddma_chan;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		au1xxx_dbdma_start(c);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		au1xxx_dbdma_stop(c);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}