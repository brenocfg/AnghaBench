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
struct priv {int paused; int final_chunk_written; int /*<<< orphan*/  alsa; scalar_t__ delay_before_pause; scalar_t__ prepause_frames; } ;
struct ao {scalar_t__ stream_silence; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 int snd_pcm_drop (int /*<<< orphan*/ ) ; 
 int snd_pcm_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_reset (struct ao*) ; 

__attribute__((used)) static void reset(struct ao *ao)
{
    struct priv *p = ao->priv;
    int err;

    p->paused = false;
    p->prepause_frames = 0;
    p->delay_before_pause = 0;
    p->final_chunk_written = false;

    if (ao->stream_silence) {
        soft_reset(ao);
    } else {
        err = snd_pcm_drop(p->alsa);
        CHECK_ALSA_ERROR("pcm prepare error");
        err = snd_pcm_prepare(p->alsa);
        CHECK_ALSA_ERROR("pcm prepare error");
    }

alsa_error: ;
}