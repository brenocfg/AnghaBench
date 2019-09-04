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
struct voice {int flags; int period_size; int vperiod; int sync_cso; int sync_buffer_size; int sync_period_size; scalar_t__ buffer_size; int /*<<< orphan*/  substream; scalar_t__ sync_base; } ;

/* Variables and functions */
 scalar_t__ SIS_CAPTURE_DMA_FORMAT_CSO ; 
 int VOICE_SSO_TIMING ; 
 int VOICE_SYNC_TIMING ; 
 scalar_t__ readw (scalar_t__) ; 
 int /*<<< orphan*/  sis_update_sso (struct voice*,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_update_voice(struct voice *voice)
{
	if (voice->flags & VOICE_SSO_TIMING) {
		sis_update_sso(voice, voice->period_size);
	} else if (voice->flags & VOICE_SYNC_TIMING) {
		int sync;

		/* If we've not hit the end of the virtual period, update
		 * our records and keep going.
		 */
		if (voice->vperiod > voice->period_size) {
			voice->vperiod -= voice->period_size;
			if (voice->vperiod < voice->period_size)
				sis_update_sso(voice, voice->vperiod);
			else
				sis_update_sso(voice, voice->period_size);
			return;
		}

		/* Calculate our relative offset between the target and
		 * the actual CSO value. Since we're operating in a loop,
		 * if the value is more than half way around, we can
		 * consider ourselves wrapped.
		 */
		sync = voice->sync_cso;
		sync -= readw(voice->sync_base + SIS_CAPTURE_DMA_FORMAT_CSO);
		if (sync > (voice->sync_buffer_size / 2))
			sync -= voice->sync_buffer_size;

		/* If sync is positive, then we interrupted too early, and
		 * we'll need to come back in a few samples and try again.
		 * There's a minimum wait, as it takes some time for the DMA
		 * engine to startup, etc...
		 */
		if (sync > 0) {
			if (sync < 16)
				sync = 16;
			sis_update_sso(voice, sync);
			return;
		}

		/* Ok, we interrupted right on time, or (hopefully) just
		 * a bit late. We'll adjst our next waiting period based
		 * on how close we got.
		 *
		 * We need to stay just behind the actual channel to ensure
		 * it really is past a period when we get our interrupt --
		 * otherwise we'll fall into the early code above and have
		 * a minimum wait time, which makes us quite late here,
		 * eating into the user's time to refresh the buffer, esp.
		 * if using small periods.
		 *
		 * If we're less than 9 samples behind, we're on target.
		 * Otherwise, shorten the next vperiod by the amount we've
		 * been delayed.
		 */
		if (sync > -9)
			voice->vperiod = voice->sync_period_size + 1;
		else
			voice->vperiod = voice->sync_period_size + sync + 10;

		if (voice->vperiod < voice->buffer_size) {
			sis_update_sso(voice, voice->vperiod);
			voice->vperiod = 0;
		} else
			sis_update_sso(voice, voice->period_size);

		sync = voice->sync_cso + voice->sync_period_size;
		if (sync >= voice->sync_buffer_size)
			sync -= voice->sync_buffer_size;
		voice->sync_cso = sync;
	}

	snd_pcm_period_elapsed(voice->substream);
}