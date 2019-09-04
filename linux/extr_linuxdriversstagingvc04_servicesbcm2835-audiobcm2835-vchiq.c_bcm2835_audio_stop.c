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
struct bcm2835_alsa_stream {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_AUDIO_MSG_TYPE_STOP ; 
 int bcm2835_audio_send_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bcm2835_audio_stop(struct bcm2835_alsa_stream *alsa_stream)
{
	return bcm2835_audio_send_simple(alsa_stream->instance,
					 VC_AUDIO_MSG_TYPE_STOP, false);
}