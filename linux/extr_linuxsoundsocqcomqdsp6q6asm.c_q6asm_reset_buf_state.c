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
struct audio_port_data {scalar_t__ dsp_buf; } ;
struct audio_client {int /*<<< orphan*/  lock; struct audio_port_data* port; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void q6asm_reset_buf_state(struct audio_client *ac)
{
	struct audio_port_data *port = NULL;
	unsigned long flags;

	spin_lock_irqsave(&ac->lock, flags);
	port = &ac->port[SNDRV_PCM_STREAM_PLAYBACK];
	port->dsp_buf = 0;
	port = &ac->port[SNDRV_PCM_STREAM_CAPTURE];
	port->dsp_buf = 0;
	spin_unlock_irqrestore(&ac->lock, flags);
}