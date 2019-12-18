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
struct priv {int paused; scalar_t__ prepause_frames; int /*<<< orphan*/  alsa; scalar_t__ can_pause; } ;
struct ao {scalar_t__ stream_silence; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*) ; 
 scalar_t__ SND_PCM_STATE_PAUSED ; 
 int /*<<< orphan*/  ao_play_silence (struct ao*,scalar_t__) ; 
 int /*<<< orphan*/  get_delay (struct ao*) ; 
 int /*<<< orphan*/  resume_device (struct ao*) ; 
 int snd_pcm_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_prepare (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audio_resume(struct ao *ao)
{
    struct priv *p = ao->priv;
    int err;

    if (!p->paused)
        return;

    resume_device(ao);

    if (ao->stream_silence) {
        p->paused = false;
        get_delay(ao); // recovers from underrun (as a side-effect)
    } else if (p->can_pause) {
        if (snd_pcm_state(p->alsa) == SND_PCM_STATE_PAUSED) {
            err = snd_pcm_pause(p->alsa, 0);
            CHECK_ALSA_ERROR("pcm resume error");
        }
    } else {
        MP_VERBOSE(ao, "resume not supported by hardware\n");
        err = snd_pcm_prepare(p->alsa);
        CHECK_ALSA_ERROR("pcm prepare error");
    }

    if (p->prepause_frames)
        ao_play_silence(ao, p->prepause_frames);

alsa_error: ;
    p->paused = false;
}