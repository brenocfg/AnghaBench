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
struct priv {int /*<<< orphan*/ * alsa; int /*<<< orphan*/ * output; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 int /*<<< orphan*/  snd_output_close (int /*<<< orphan*/ *) ; 
 int snd_pcm_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *p = ao->priv;

    if (p->output)
        snd_output_close(p->output);
    p->output = NULL;

    if (p->alsa) {
        int err;

        err = snd_pcm_close(p->alsa);
        p->alsa = NULL;
        CHECK_ALSA_ERROR("pcm close error");
    }

alsa_error: ;
}