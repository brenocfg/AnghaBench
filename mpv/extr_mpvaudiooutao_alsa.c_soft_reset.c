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
struct priv {int /*<<< orphan*/  alsa; } ;
struct ao {struct priv* priv; } ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_WARN (char*) ; 
 scalar_t__ SND_PCM_STATE_RUNNING ; 
 int snd_pcm_rewind (int /*<<< orphan*/ ,int) ; 
 int snd_pcm_rewindable (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soft_reset(struct ao *ao)
{
    struct priv *p = ao->priv;
    snd_pcm_sframes_t frames = snd_pcm_rewindable(p->alsa);
    if (frames > 0 && snd_pcm_state(p->alsa) == SND_PCM_STATE_RUNNING) {
        frames = snd_pcm_rewind(p->alsa, frames);
        if (frames < 0) {
            int err = frames;
            CHECK_ALSA_WARN("pcm rewind error");
        }
    }
}