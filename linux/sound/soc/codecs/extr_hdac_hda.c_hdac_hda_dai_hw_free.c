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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; } ;
struct hdac_hda_priv {int /*<<< orphan*/  codec; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_pcm {struct hda_pcm_stream* stream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_hda_codec_cleanup (int /*<<< orphan*/ *,struct hda_pcm_stream*,struct snd_pcm_substream*) ; 
 struct hdac_hda_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct hda_pcm* snd_soc_find_pcm_from_dai (struct hdac_hda_priv*,struct snd_soc_dai*) ; 

__attribute__((used)) static int hdac_hda_dai_hw_free(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct hdac_hda_priv *hda_pvt;
	struct hda_pcm_stream *hda_stream;
	struct hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_drvdata(component);
	pcm = snd_soc_find_pcm_from_dai(hda_pvt, dai);
	if (!pcm)
		return -EINVAL;

	hda_stream = &pcm->stream[substream->stream];
	snd_hda_codec_cleanup(&hda_pvt->codec, hda_stream, substream);

	return 0;
}