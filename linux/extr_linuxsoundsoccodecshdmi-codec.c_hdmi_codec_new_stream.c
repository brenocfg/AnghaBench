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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct hdmi_codec_priv {int /*<<< orphan*/  current_stream_lock; struct snd_pcm_substream* current_stream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hdmi_codec_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int hdmi_codec_new_stream(struct snd_pcm_substream *substream,
				 struct snd_soc_dai *dai)
{
	struct hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);
	int ret = 0;

	mutex_lock(&hcp->current_stream_lock);
	if (!hcp->current_stream) {
		hcp->current_stream = substream;
	} else if (hcp->current_stream != substream) {
		dev_err(dai->dev, "Only one simultaneous stream supported!\n");
		ret = -EINVAL;
	}
	mutex_unlock(&hcp->current_stream_lock);

	return ret;
}