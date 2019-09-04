#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int playing; scalar_t__ capturing; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct snd_harmony {int /*<<< orphan*/  lock; TYPE_3__ sdma; TYPE_4__ st; TYPE_2__ gdma; TYPE_1__ pbuf; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  HARMONY_PNXTADD ; 
 int /*<<< orphan*/  HARMONY_RNXTADD ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 132 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  harmony_disable_interrupts (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_enable_interrupts (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_mute (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_unmute (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_write (struct snd_harmony*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct snd_harmony* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_harmony_playback_trigger(struct snd_pcm_substream *ss, int cmd)
{
	struct snd_harmony *h = snd_pcm_substream_chip(ss);

	if (h->st.capturing)
		return -EBUSY;

	spin_lock(&h->lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		h->st.playing = 1;
		harmony_write(h, HARMONY_PNXTADD, h->pbuf.addr);
		harmony_write(h, HARMONY_RNXTADD, h->gdma.addr);
		harmony_unmute(h);
		harmony_enable_interrupts(h);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		h->st.playing = 0;
		harmony_mute(h);
		harmony_write(h, HARMONY_PNXTADD, h->sdma.addr);
		harmony_disable_interrupts(h);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	default:
		spin_unlock(&h->lock);
		snd_BUG();
		return -EINVAL;
	}
	spin_unlock(&h->lock);
	
	return 0;
}