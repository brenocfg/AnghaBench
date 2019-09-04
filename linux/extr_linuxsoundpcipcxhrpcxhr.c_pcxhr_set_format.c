#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {TYPE_2__* card; TYPE_4__* mgr; } ;
struct pcxhr_stream {int format; int channels; TYPE_1__* pipe; TYPE_3__* substream; } ;
struct pcxhr_rmh {int* cmd; int cmd_len; } ;
struct TYPE_9__ {int sample_rate; } ;
struct TYPE_8__ {int number; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int is_capture; int /*<<< orphan*/  first_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FORMAT_STREAM_IN ; 
 int /*<<< orphan*/  CMD_FORMAT_STREAM_OUT ; 
 scalar_t__ DSP_EXT_CMD_SET (TYPE_4__*) ; 
 int EINVAL ; 
 unsigned int HEADER_FMT_16BITS ; 
 unsigned int HEADER_FMT_24BITS ; 
 unsigned int HEADER_FMT_BASE_FLOAT ; 
 unsigned int HEADER_FMT_BASE_LIN ; 
 unsigned int HEADER_FMT_INTEL ; 
 unsigned int HEADER_FMT_MONO ; 
 unsigned int HEADER_FMT_UPTO11 ; 
 unsigned int HEADER_FMT_UPTO32 ; 
#define  SNDRV_PCM_FORMAT_FLOAT_LE 133 
#define  SNDRV_PCM_FORMAT_S16_BE 132 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S24_3BE 130 
#define  SNDRV_PCM_FORMAT_S24_3LE 129 
#define  SNDRV_PCM_FORMAT_U8 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (TYPE_4__*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_set_pipe_cmd_params (struct pcxhr_rmh*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_pcxhr* snd_pcm_substream_chip (TYPE_3__*) ; 

__attribute__((used)) static int pcxhr_set_format(struct pcxhr_stream *stream)
{
	int err, is_capture, sample_rate, stream_num;
	struct snd_pcxhr *chip;
	struct pcxhr_rmh rmh;
	unsigned int header;

	chip = snd_pcm_substream_chip(stream->substream);
	switch (stream->format) {
	case SNDRV_PCM_FORMAT_U8:
		header = HEADER_FMT_BASE_LIN;
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		header = HEADER_FMT_BASE_LIN |
			 HEADER_FMT_16BITS | HEADER_FMT_INTEL;
		break;
	case SNDRV_PCM_FORMAT_S16_BE:
		header = HEADER_FMT_BASE_LIN | HEADER_FMT_16BITS;
		break;
	case SNDRV_PCM_FORMAT_S24_3LE:
		header = HEADER_FMT_BASE_LIN |
			 HEADER_FMT_24BITS | HEADER_FMT_INTEL;
		break;
	case SNDRV_PCM_FORMAT_S24_3BE:
		header = HEADER_FMT_BASE_LIN | HEADER_FMT_24BITS;
		break;
	case SNDRV_PCM_FORMAT_FLOAT_LE:
		header = HEADER_FMT_BASE_FLOAT | HEADER_FMT_INTEL;
		break;
	default:
		dev_err(chip->card->dev,
			"error pcxhr_set_format() : unknown format\n");
		return -EINVAL;
	}

	sample_rate = chip->mgr->sample_rate;
	if (sample_rate <= 32000 && sample_rate !=0) {
		if (sample_rate <= 11025)
			header |= HEADER_FMT_UPTO11;
		else
			header |= HEADER_FMT_UPTO32;
	}
	if (stream->channels == 1)
		header |= HEADER_FMT_MONO;

	is_capture = stream->pipe->is_capture;
	stream_num = is_capture ? 0 : stream->substream->number;

	pcxhr_init_rmh(&rmh, is_capture ?
		       CMD_FORMAT_STREAM_IN : CMD_FORMAT_STREAM_OUT);
	pcxhr_set_pipe_cmd_params(&rmh, is_capture, stream->pipe->first_audio,
				  stream_num, 0);
	if (is_capture) {
		/* bug with old dsp versions: */
		/* bit 12 also sets the format of the playback stream */
		if (DSP_EXT_CMD_SET(chip->mgr))
			rmh.cmd[0] |= 1<<10;
		else
			rmh.cmd[0] |= 1<<12;
	}
	rmh.cmd[1] = 0;
	rmh.cmd_len = 2;
	if (DSP_EXT_CMD_SET(chip->mgr)) {
		/* add channels and set bit 19 if channels>2 */
		rmh.cmd[1] = stream->channels;
		if (!is_capture) {
			/* playback : add channel mask to command */
			rmh.cmd[2] = (stream->channels == 1) ? 0x01 : 0x03;
			rmh.cmd_len = 3;
		}
	}
	rmh.cmd[rmh.cmd_len++] = header >> 8;
	rmh.cmd[rmh.cmd_len++] = (header & 0xff) << 16;
	err = pcxhr_send_msg(chip->mgr, &rmh);
	if (err)
		dev_err(chip->card->dev,
			"ERROR pcxhr_set_format err=%x;\n", err);
	return err;
}