#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ buffer_pos; scalar_t__ period_pos; } ;
struct ua101 {TYPE_2__ playback; int /*<<< orphan*/  states; int /*<<< orphan*/  alsa_playback_wait; int /*<<< orphan*/  mutex; } ;
struct snd_pcm_substream {TYPE_1__* runtime; struct ua101* private_data; } ;
struct TYPE_3__ {scalar_t__ delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  PLAYBACK_URB_COMPLETED ; 
 int /*<<< orphan*/  USB_PLAYBACK_RUNNING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int start_usb_capture (struct ua101*) ; 
 int start_usb_playback (struct ua101*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int playback_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct ua101 *ua = substream->private_data;
	int err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	if (err >= 0)
		err = start_usb_playback(ua);
	mutex_unlock(&ua->mutex);
	if (err < 0)
		return err;

	/* see the comment in capture_pcm_prepare() */
	wait_event(ua->alsa_playback_wait,
		   test_bit(PLAYBACK_URB_COMPLETED, &ua->states) ||
		   !test_bit(USB_PLAYBACK_RUNNING, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states))
		return -ENODEV;
	if (!test_bit(USB_PLAYBACK_RUNNING, &ua->states))
		return -EIO;

	substream->runtime->delay = 0;
	ua->playback.period_pos = 0;
	ua->playback.buffer_pos = 0;
	return 0;
}