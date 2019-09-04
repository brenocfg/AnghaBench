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
struct TYPE_6__ {int queue_length; int /*<<< orphan*/  channels; struct snd_pcm_substream* substream; } ;
struct ua101 {int rate; int /*<<< orphan*/  mutex; int /*<<< orphan*/  states; int /*<<< orphan*/  packets_per_second; TYPE_3__ playback; } ;
struct snd_pcm_substream {TYPE_2__* runtime; struct ua101* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  fifo_size; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALSA_CAPTURE_OPEN ; 
 int /*<<< orphan*/  ALSA_PLAYBACK_OPEN ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int set_stream_hw (struct ua101*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int start_usb_capture (struct ua101*) ; 
 int start_usb_playback (struct ua101*) ; 
 int /*<<< orphan*/  stop_usb_capture (struct ua101*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int playback_pcm_open(struct snd_pcm_substream *substream)
{
	struct ua101 *ua = substream->private_data;
	int err;

	ua->playback.substream = substream;
	err = set_stream_hw(ua, substream, ua->playback.channels);
	if (err < 0)
		return err;
	substream->runtime->hw.fifo_size =
		DIV_ROUND_CLOSEST(ua->rate * ua->playback.queue_length,
				  ua->packets_per_second);

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	if (err < 0)
		goto error;
	err = start_usb_playback(ua);
	if (err < 0) {
		if (!test_bit(ALSA_CAPTURE_OPEN, &ua->states))
			stop_usb_capture(ua);
		goto error;
	}
	set_bit(ALSA_PLAYBACK_OPEN, &ua->states);
error:
	mutex_unlock(&ua->mutex);
	return err;
}