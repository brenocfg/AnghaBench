#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  profile; int /*<<< orphan*/  id; } ;
struct snd_compr_params {TYPE_3__ codec; } ;
struct uniphier_aio_sub {int setting; struct snd_compr_params cparams; int /*<<< orphan*/  iec_pc; } ;
struct uniphier_aio {TYPE_2__* chip; struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_compr_stream {size_t direction; struct snd_soc_pcm_runtime* private_data; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEC61937_PC_AAC ; 
 int /*<<< orphan*/  SND_AUDIOCODEC_IEC61937 ; 
 int /*<<< orphan*/  SND_AUDIOPROFILE_IEC61937_SPDIF ; 
 int /*<<< orphan*/  aio_port_reset (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aio_src_reset (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int uniphier_aio_compr_prepare (struct snd_compr_stream*) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aio_compr_set_params(struct snd_compr_stream *cstream,
					 struct snd_compr_params *params)
{
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	struct device *dev = &aio->chip->pdev->dev;
	int ret;

	if (params->codec.id != SND_AUDIOCODEC_IEC61937) {
		dev_err(dev, "Codec ID is not supported(%d)\n",
			params->codec.id);
		return -EINVAL;
	}
	if (params->codec.profile != SND_AUDIOPROFILE_IEC61937_SPDIF) {
		dev_err(dev, "Codec profile is not supported(%d)\n",
			params->codec.profile);
		return -EINVAL;
	}

	/* IEC frame type will be changed after received valid data */
	sub->iec_pc = IEC61937_PC_AAC;

	sub->cparams = *params;
	sub->setting = 1;

	aio_port_reset(sub);
	aio_src_reset(sub);

	ret = uniphier_aio_compr_prepare(cstream);
	if (ret)
		return ret;

	return 0;
}