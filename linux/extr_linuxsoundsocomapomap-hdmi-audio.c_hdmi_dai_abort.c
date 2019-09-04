#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hdmi_audio_data {int /*<<< orphan*/  current_stream_lock; TYPE_1__* current_stream; } ;
struct device {int dummy; } ;
struct TYPE_5__ {scalar_t__ runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct hdmi_audio_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pcm_running (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_pcm_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (TYPE_1__*) ; 

__attribute__((used)) static void hdmi_dai_abort(struct device *dev)
{
	struct hdmi_audio_data *ad = dev_get_drvdata(dev);

	mutex_lock(&ad->current_stream_lock);
	if (ad->current_stream && ad->current_stream->runtime &&
	    snd_pcm_running(ad->current_stream)) {
		dev_err(dev, "HDMI display disabled, aborting playback\n");
		snd_pcm_stream_lock_irq(ad->current_stream);
		snd_pcm_stop(ad->current_stream, SNDRV_PCM_STATE_DISCONNECTED);
		snd_pcm_stream_unlock_irq(ad->current_stream);
	}
	mutex_unlock(&ad->current_stream_lock);
}