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
struct priv {double delay_before_pause; int /*<<< orphan*/  alsa; scalar_t__ paused; } ;
struct ao {scalar_t__ samplerate; struct priv* priv; } ;
typedef  double snd_pcm_sframes_t ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  handle_underrun (struct ao*) ; 
 int snd_pcm_delay (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  snd_pcm_forward (int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct priv *p = ao->priv;
    snd_pcm_sframes_t delay;

    if (p->paused)
        return p->delay_before_pause;

    int err = snd_pcm_delay(p->alsa, &delay);
    if (err < 0) {
        if (err == -EPIPE)
            handle_underrun(ao);
        return 0;
    }

    if (delay < 0) {
        /* underrun - move the application pointer forward to catch up */
        snd_pcm_forward(p->alsa, -delay);
        delay = 0;
    }
    return delay / (double)ao->samplerate;
}