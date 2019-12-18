#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct snd_soc_tplg_stream_caps* caps; int /*<<< orphan*/  pcm_id; } ;
struct snd_sof_pcm {int* prepared; TYPE_5__* stream; TYPE_2__ pcm; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_stream_caps {int /*<<< orphan*/  buffer_size_max; int /*<<< orphan*/  periods_max; int /*<<< orphan*/  periods_min; int /*<<< orphan*/  period_size_max; int /*<<< orphan*/  period_size_min; int /*<<< orphan*/  formats; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; int wait_time; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_8__ {int info; void* buffer_bytes_max; void* periods_max; void* periods_min; void* period_bytes_max; void* period_bytes_min; int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_3__ hw; } ;
struct TYPE_9__ {scalar_t__ dai_posn; scalar_t__ host_posn; } ;
struct TYPE_10__ {struct snd_pcm_substream* substream; TYPE_4__ posn; int /*<<< orphan*/  period_elapsed_work; } ;
struct TYPE_6__ {scalar_t__ no_pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int SNDRV_PCM_INFO_INTERLEAVED ; 
 int SNDRV_PCM_INFO_MMAP ; 
 int SNDRV_PCM_INFO_MMAP_VALID ; 
 int SNDRV_PCM_INFO_NO_PERIOD_WAKEUP ; 
 int SNDRV_PCM_INFO_PAUSE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_dai (struct snd_sof_dev*,struct snd_soc_pcm_runtime*) ; 
 int snd_sof_pcm_platform_open (struct snd_sof_dev*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  sof_pcm_period_elapsed_work ; 

__attribute__((used)) static int sof_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_pcm *spcm;
	struct snd_soc_tplg_stream_caps *caps;
	int ret;

	/* nothing to do for BE */
	if (rtd->dai_link->no_pcm)
		return 0;

	spcm = snd_sof_find_spcm_dai(sdev, rtd);
	if (!spcm)
		return -EINVAL;

	dev_dbg(sdev->dev, "pcm: open stream %d dir %d\n", spcm->pcm.pcm_id,
		substream->stream);

	INIT_WORK(&spcm->stream[substream->stream].period_elapsed_work,
		  sof_pcm_period_elapsed_work);

	caps = &spcm->pcm.caps[substream->stream];

	/* set any runtime constraints based on topology */
	snd_pcm_hw_constraint_step(substream->runtime, 0,
				   SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   le32_to_cpu(caps->period_size_min));
	snd_pcm_hw_constraint_step(substream->runtime, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   le32_to_cpu(caps->period_size_min));

	/* set runtime config */
	runtime->hw.info = SNDRV_PCM_INFO_MMAP |
			  SNDRV_PCM_INFO_MMAP_VALID |
			  SNDRV_PCM_INFO_INTERLEAVED |
			  SNDRV_PCM_INFO_PAUSE |
			  SNDRV_PCM_INFO_NO_PERIOD_WAKEUP;
	runtime->hw.formats = le64_to_cpu(caps->formats);
	runtime->hw.period_bytes_min = le32_to_cpu(caps->period_size_min);
	runtime->hw.period_bytes_max = le32_to_cpu(caps->period_size_max);
	runtime->hw.periods_min = le32_to_cpu(caps->periods_min);
	runtime->hw.periods_max = le32_to_cpu(caps->periods_max);

	/*
	 * caps->buffer_size_min is not used since the
	 * snd_pcm_hardware structure only defines buffer_bytes_max
	 */
	runtime->hw.buffer_bytes_max = le32_to_cpu(caps->buffer_size_max);

	dev_dbg(sdev->dev, "period min %zd max %zd bytes\n",
		runtime->hw.period_bytes_min,
		runtime->hw.period_bytes_max);
	dev_dbg(sdev->dev, "period count %d max %d\n",
		runtime->hw.periods_min,
		runtime->hw.periods_max);
	dev_dbg(sdev->dev, "buffer max %zd bytes\n",
		runtime->hw.buffer_bytes_max);

	/* set wait time - TODO: come from topology */
	substream->wait_time = 500;

	spcm->stream[substream->stream].posn.host_posn = 0;
	spcm->stream[substream->stream].posn.dai_posn = 0;
	spcm->stream[substream->stream].substream = substream;
	spcm->prepared[substream->stream] = false;

	ret = snd_sof_pcm_platform_open(sdev, substream);
	if (ret < 0)
		dev_err(sdev->dev, "error: pcm open failed %d\n", ret);

	return ret;
}