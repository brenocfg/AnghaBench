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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct hdmi_audio_data {int /*<<< orphan*/  current_stream_lock; struct snd_pcm_substream* current_stream; int /*<<< orphan*/  dssdev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* audio_shutdown ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct hdmi_audio_data* card_drvdata_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_dai_shutdown(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct hdmi_audio_data *ad = card_drvdata_substream(substream);

	WARN_ON(ad->current_stream != substream);

	ad->ops->audio_shutdown(ad->dssdev);

	mutex_lock(&ad->current_stream_lock);
	ad->current_stream = NULL;
	mutex_unlock(&ad->current_stream_lock);
}