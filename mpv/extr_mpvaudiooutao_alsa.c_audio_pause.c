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
struct priv {int paused; int delay_before_pause; int prepause_frames; int /*<<< orphan*/  alsa; scalar_t__ can_pause; } ;
struct ao {int samplerate; scalar_t__ stream_silence; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 scalar_t__ SND_PCM_STATE_RUNNING ; 
 int get_delay (struct ao*) ; 
 int snd_pcm_drop (int /*<<< orphan*/ ) ; 
 int snd_pcm_pause (int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_pcm_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_reset (struct ao*) ; 

__attribute__((used)) static void audio_pause(struct ao *ao)
{
    struct priv *p = ao->priv;
    int err;

    if (p->paused)
        return;

    p->delay_before_pause = get_delay(ao);
    p->prepause_frames = p->delay_before_pause * ao->samplerate;

    if (ao->stream_silence) {
        soft_reset(ao);
    } else if (p->can_pause) {
        if (snd_pcm_state(p->alsa) == SND_PCM_STATE_RUNNING) {
            err = snd_pcm_pause(p->alsa, 1);
            CHECK_ALSA_ERROR("pcm pause error");
            p->prepause_frames = 0;
        }
    } else {
        err = snd_pcm_drop(p->alsa);
        CHECK_ALSA_ERROR("pcm drop error");
    }

    p->paused = true;

alsa_error: ;
}