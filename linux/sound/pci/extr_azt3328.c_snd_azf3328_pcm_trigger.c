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
typedef  int u16 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; int /*<<< orphan*/  rate; struct snd_azf3328_codec_data* private_data; } ;
struct snd_azf3328_codec_data {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;
struct snd_azf3328 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AZF_CODEC_PLAYBACK ; 
 int DMA_EPILOGUE_SOMETHING ; 
 int DMA_RESUME ; 
 int DMA_RUN_SOMETHING1 ; 
 int DMA_RUN_SOMETHING2 ; 
 int DMA_SOMETHING_ELSE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IDX_IO_CODEC_DMA_FLAGS ; 
 int /*<<< orphan*/  IDX_IO_CODEC_IRQTYPE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int SOMETHING_ALMOST_ALWAYS_SET ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int snd_azf3328_codec_inw (struct snd_azf3328_codec_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_codec_outw (struct snd_azf3328_codec_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_azf3328_codec_setdmaa (struct snd_azf3328*,struct snd_azf3328_codec_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_codec_setfmt (struct snd_azf3328_codec_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_ctrl_codec_activity (struct snd_azf3328*,scalar_t__,int) ; 
 int snd_azf3328_mixer_mute_control_pcm (struct snd_azf3328*,int) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_azf3328* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_azf3328_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_azf3328_codec_data *codec = runtime->private_data;
	int result = 0;
	u16 flags1;
	bool previously_muted = false;
	bool is_main_mixer_playback_codec = (AZF_CODEC_PLAYBACK == codec->type);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		dev_dbg(chip->card->dev, "START PCM %s\n", codec->name);

		if (is_main_mixer_playback_codec) {
			/* mute WaveOut (avoid clicking during setup) */
			previously_muted =
				snd_azf3328_mixer_mute_control_pcm(
						chip, 1
				);
		}

		snd_azf3328_codec_setfmt(codec,
			runtime->rate,
			snd_pcm_format_width(runtime->format),
			runtime->channels);

		spin_lock(codec->lock);
		/* first, remember current value: */
		flags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS);

		/* stop transfer */
		flags1 &= ~DMA_RESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* FIXME: clear interrupts or what??? */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_IRQTYPE, 0xffff);
		spin_unlock(codec->lock);

		snd_azf3328_codec_setdmaa(chip, codec, runtime->dma_addr,
			snd_pcm_lib_period_bytes(substream),
			snd_pcm_lib_buffer_bytes(substream)
		);

		spin_lock(codec->lock);
#ifdef WIN9X
		/* FIXME: enable playback/recording??? */
		flags1 |= DMA_RUN_SOMETHING1 | DMA_RUN_SOMETHING2;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* start transfer again */
		/* FIXME: what is this value (0x0010)??? */
		flags1 |= DMA_RESUME | DMA_EPILOGUE_SOMETHING;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);
#else /* NT4 */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			0x0000);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RUN_SOMETHING1);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RUN_SOMETHING1 |
			DMA_RUN_SOMETHING2);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RESUME |
			SOMETHING_ALMOST_ALWAYS_SET |
			DMA_EPILOGUE_SOMETHING |
			DMA_SOMETHING_ELSE);
#endif
		spin_unlock(codec->lock);
		snd_azf3328_ctrl_codec_activity(chip, codec->type, 1);

		if (is_main_mixer_playback_codec) {
			/* now unmute WaveOut */
			if (!previously_muted)
				snd_azf3328_mixer_mute_control_pcm(
						chip, 0
				);
		}

		dev_dbg(chip->card->dev, "PCM STARTED %s\n", codec->name);
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
		dev_dbg(chip->card->dev, "PCM RESUME %s\n", codec->name);
		/* resume codec if we were active */
		spin_lock(codec->lock);
		if (codec->running)
			snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
				snd_azf3328_codec_inw(
					codec, IDX_IO_CODEC_DMA_FLAGS
				) | DMA_RESUME
			);
		spin_unlock(codec->lock);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(chip->card->dev, "PCM STOP %s\n", codec->name);

		if (is_main_mixer_playback_codec) {
			/* mute WaveOut (avoid clicking during setup) */
			previously_muted =
				snd_azf3328_mixer_mute_control_pcm(
						chip, 1
				);
		}

		spin_lock(codec->lock);
		/* first, remember current value: */
		flags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS);

		/* stop transfer */
		flags1 &= ~DMA_RESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* hmm, is this really required? we're resetting the same bit
		 * immediately thereafter... */
		flags1 |= DMA_RUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		flags1 &= ~DMA_RUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);
		spin_unlock(codec->lock);
		snd_azf3328_ctrl_codec_activity(chip, codec->type, 0);

		if (is_main_mixer_playback_codec) {
			/* now unmute WaveOut */
			if (!previously_muted)
				snd_azf3328_mixer_mute_control_pcm(
						chip, 0
				);
		}

		dev_dbg(chip->card->dev, "PCM STOPPED %s\n", codec->name);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		dev_dbg(chip->card->dev, "PCM SUSPEND %s\n", codec->name);
		/* make sure codec is stopped */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			snd_azf3328_codec_inw(
				codec, IDX_IO_CODEC_DMA_FLAGS
			) & ~DMA_RESUME
		);
		break;
        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		WARN(1, "FIXME: SNDRV_PCM_TRIGGER_PAUSE_PUSH NIY!\n");
                break;
        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		WARN(1, "FIXME: SNDRV_PCM_TRIGGER_PAUSE_RELEASE NIY!\n");
                break;
        default:
		WARN(1, "FIXME: unknown trigger mode!\n");
                return -EINVAL;
	}

	return result;
}