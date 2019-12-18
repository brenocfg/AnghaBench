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

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MP_INFO (struct ao*,char*) ; 
 scalar_t__ SND_PCM_STATE_SUSPENDED ; 
 int /*<<< orphan*/  sleep (int) ; 
 int snd_pcm_resume (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resume_device(struct ao *ao)
{
    struct priv *p = ao->priv;
    int err;

    if (snd_pcm_state(p->alsa) == SND_PCM_STATE_SUSPENDED) {
        MP_INFO(ao, "PCM in suspend mode, trying to resume.\n");

        while ((err = snd_pcm_resume(p->alsa)) == -EAGAIN)
            sleep(1);
    }
}