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
struct xen_snd_front_pcm_stream_info {TYPE_1__* evt_pair; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int XENSND_OP_TRIGGER_PAUSE ; 
 int XENSND_OP_TRIGGER_RESUME ; 
 int XENSND_OP_TRIGGER_START ; 
 int XENSND_OP_TRIGGER_STOP ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 int xen_snd_front_stream_trigger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int alsa_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	int type;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		type = XENSND_OP_TRIGGER_START;
		break;

	case SNDRV_PCM_TRIGGER_RESUME:
		type = XENSND_OP_TRIGGER_RESUME;
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		type = XENSND_OP_TRIGGER_STOP;
		break;

	case SNDRV_PCM_TRIGGER_SUSPEND:
		type = XENSND_OP_TRIGGER_PAUSE;
		break;

	default:
		return -EINVAL;
	}

	return xen_snd_front_stream_trigger(&stream->evt_pair->req, type);
}