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
struct bcm2835_audio_instance {int dummy; } ;
struct bcm2835_alsa_stream {struct bcm2835_audio_instance* instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_AUDIO_MSG_TYPE_CLOSE ; 
 int bcm2835_audio_send_simple (struct bcm2835_audio_instance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct bcm2835_audio_instance*) ; 
 int /*<<< orphan*/  vc_vchi_audio_deinit (struct bcm2835_audio_instance*) ; 

int bcm2835_audio_close(struct bcm2835_alsa_stream *alsa_stream)
{
	struct bcm2835_audio_instance *instance = alsa_stream->instance;
	int err;

	err = bcm2835_audio_send_simple(alsa_stream->instance,
					VC_AUDIO_MSG_TYPE_CLOSE, true);

	/* Stop the audio service */
	vc_vchi_audio_deinit(instance);
	alsa_stream->instance = NULL;
	kfree(instance);

	return err;
}