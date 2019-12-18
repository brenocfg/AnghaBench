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
struct soc_tplg {int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_stream {int dummy; } ;
struct snd_soc_tplg_pcm_v4 {int /*<<< orphan*/ * caps; int /*<<< orphan*/ * stream; int /*<<< orphan*/  num_streams; int /*<<< orphan*/  compress; int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; int /*<<< orphan*/  dai_id; int /*<<< orphan*/  pcm_id; int /*<<< orphan*/ * dai_name; int /*<<< orphan*/ * pcm_name; } ;
struct snd_soc_tplg_pcm {int /*<<< orphan*/ * caps; int /*<<< orphan*/ * stream; int /*<<< orphan*/  num_streams; int /*<<< orphan*/  compress; int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; int /*<<< orphan*/  dai_id; int /*<<< orphan*/  pcm_id; int /*<<< orphan*/ * dai_name; int /*<<< orphan*/ * pcm_name; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_tplg_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stream_caps_new_ver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcm_new_ver(struct soc_tplg *tplg,
		       struct snd_soc_tplg_pcm *src,
		       struct snd_soc_tplg_pcm **pcm)
{
	struct snd_soc_tplg_pcm *dest;
	struct snd_soc_tplg_pcm_v4 *src_v4;
	int i;

	*pcm = NULL;

	if (le32_to_cpu(src->size) != sizeof(*src_v4)) {
		dev_err(tplg->dev, "ASoC: invalid PCM size\n");
		return -EINVAL;
	}

	dev_warn(tplg->dev, "ASoC: old version of PCM\n");
	src_v4 = (struct snd_soc_tplg_pcm_v4 *)src;
	dest = kzalloc(sizeof(*dest), GFP_KERNEL);
	if (!dest)
		return -ENOMEM;

	dest->size = cpu_to_le32(sizeof(*dest)); /* size of latest abi version */
	memcpy(dest->pcm_name, src_v4->pcm_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	memcpy(dest->dai_name, src_v4->dai_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	dest->pcm_id = src_v4->pcm_id;
	dest->dai_id = src_v4->dai_id;
	dest->playback = src_v4->playback;
	dest->capture = src_v4->capture;
	dest->compress = src_v4->compress;
	dest->num_streams = src_v4->num_streams;
	for (i = 0; i < le32_to_cpu(dest->num_streams); i++)
		memcpy(&dest->stream[i], &src_v4->stream[i],
		       sizeof(struct snd_soc_tplg_stream));

	for (i = 0; i < 2; i++)
		stream_caps_new_ver(&dest->caps[i], &src_v4->caps[i]);

	*pcm = dest;
	return 0;
}