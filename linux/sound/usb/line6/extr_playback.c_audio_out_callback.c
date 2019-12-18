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
struct urb {TYPE_4__* iso_frame_desc; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; scalar_t__ context; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ buffer_size; } ;
struct TYPE_10__ {scalar_t__ pos_done; int bytes; int period; int /*<<< orphan*/  lock; int /*<<< orphan*/  running; int /*<<< orphan*/  unlink_urbs; int /*<<< orphan*/  active_urbs; struct urb** urbs; int /*<<< orphan*/  last_frame; } ;
struct snd_line6_pcm {TYPE_5__ out; TYPE_3__* line6; TYPE_2__* properties; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; scalar_t__ length; } ;
struct TYPE_8__ {int iso_buffers; } ;
struct TYPE_6__ {int channels_max; } ;
struct TYPE_7__ {int bytes_per_channel; TYPE_1__ playback_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXDEV ; 
 int LINE6_ISO_PACKETS ; 
 int /*<<< orphan*/  LINE6_STREAM_PCM ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 struct snd_pcm_substream* get_substream (struct snd_line6_pcm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_audio_out_urb (struct snd_line6_pcm*) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audio_out_callback(struct urb *urb)
{
	int i, index, length = 0, shutdown = 0;
	unsigned long flags;
	struct snd_line6_pcm *line6pcm = (struct snd_line6_pcm *)urb->context;
	struct snd_pcm_substream *substream =
	    get_substream(line6pcm, SNDRV_PCM_STREAM_PLAYBACK);
	const int bytes_per_frame =
		line6pcm->properties->bytes_per_channel *
		line6pcm->properties->playback_hw.channels_max;

#if USE_CLEAR_BUFFER_WORKAROUND
	memset(urb->transfer_buffer, 0, urb->transfer_buffer_length);
#endif

	line6pcm->out.last_frame = urb->start_frame;

	/* find index of URB */
	for (index = 0; index < line6pcm->line6->iso_buffers; index++)
		if (urb == line6pcm->out.urbs[index])
			break;

	if (index >= line6pcm->line6->iso_buffers)
		return;		/* URB has been unlinked asynchronously */

	for (i = 0; i < LINE6_ISO_PACKETS; i++)
		length += urb->iso_frame_desc[i].length;

	spin_lock_irqsave(&line6pcm->out.lock, flags);

	if (test_bit(LINE6_STREAM_PCM, &line6pcm->out.running)) {
		struct snd_pcm_runtime *runtime = substream->runtime;

		line6pcm->out.pos_done +=
		    length / bytes_per_frame;

		if (line6pcm->out.pos_done >= runtime->buffer_size)
			line6pcm->out.pos_done -= runtime->buffer_size;
	}

	clear_bit(index, &line6pcm->out.active_urbs);

	for (i = 0; i < LINE6_ISO_PACKETS; i++)
		if (urb->iso_frame_desc[i].status == -EXDEV) {
			shutdown = 1;
			break;
		}

	if (test_and_clear_bit(index, &line6pcm->out.unlink_urbs))
		shutdown = 1;

	if (!shutdown) {
		submit_audio_out_urb(line6pcm);

		if (test_bit(LINE6_STREAM_PCM, &line6pcm->out.running)) {
			line6pcm->out.bytes += length;
			if (line6pcm->out.bytes >= line6pcm->out.period) {
				line6pcm->out.bytes %= line6pcm->out.period;
				spin_unlock(&line6pcm->out.lock);
				snd_pcm_period_elapsed(substream);
				spin_lock(&line6pcm->out.lock);
			}
		}
	}
	spin_unlock_irqrestore(&line6pcm->out.lock, flags);
}