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
struct TYPE_4__ {int /*<<< orphan*/  channels; struct snd_pcm_substream* substream; } ;
struct ua101 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  states; int /*<<< orphan*/  packets_per_second; int /*<<< orphan*/  rate; TYPE_1__ capture; } ;
struct snd_pcm_substream {TYPE_3__* runtime; struct ua101* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  fifo_size; } ;
struct TYPE_6__ {TYPE_2__ hw; int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALSA_CAPTURE_OPEN ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int set_stream_hw (struct ua101*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int start_usb_capture (struct ua101*) ; 

__attribute__((used)) static int capture_pcm_open(struct snd_pcm_substream *substream)
{
	struct ua101 *ua = substream->private_data;
	int err;

	ua->capture.substream = substream;
	err = set_stream_hw(ua, substream, ua->capture.channels);
	if (err < 0)
		return err;
	substream->runtime->hw.fifo_size =
		DIV_ROUND_CLOSEST(ua->rate, ua->packets_per_second);
	substream->runtime->delay = substream->runtime->hw.fifo_size;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	if (err >= 0)
		set_bit(ALSA_CAPTURE_OPEN, &ua->states);
	mutex_unlock(&ua->mutex);
	return err;
}