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
struct snd_soc_dai {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct gbaudio_stream_params {int /*<<< orphan*/  state; } ;
struct gbaudio_codec_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  module_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBAUDIO_CODEC_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct gbaudio_codec_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct gbaudio_stream_params* find_dai_stream_params (struct gbaudio_codec_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_relax (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gbcodec_shutdown(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	struct gbaudio_stream_params *params;

	mutex_lock(&codec->lock);

	if (list_empty(&codec->module_list))
		dev_info(codec->dev, "No codec module available during shutdown\n");

	params = find_dai_stream_params(codec, dai->id, substream->stream);
	if (!params) {
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		return;
	}
	params->state = GBAUDIO_CODEC_SHUTDOWN;
	mutex_unlock(&codec->lock);
	pm_relax(dai->dev);
}