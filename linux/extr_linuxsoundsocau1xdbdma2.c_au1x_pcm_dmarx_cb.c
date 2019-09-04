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
struct au1xpsc_audio_dmadata {scalar_t__ curr_period; scalar_t__ periods; int /*<<< orphan*/  substream; scalar_t__ pos; scalar_t__ period_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1x_pcm_queue_rx (struct au1xpsc_audio_dmadata*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1x_pcm_dmarx_cb(int irq, void *dev_id)
{
	struct au1xpsc_audio_dmadata *cd = dev_id;

	cd->pos += cd->period_bytes;
	if (++cd->curr_period >= cd->periods) {
		cd->pos = 0;
		cd->curr_period = 0;
	}
	snd_pcm_period_elapsed(cd->substream);
	au1x_pcm_queue_rx(cd);
}