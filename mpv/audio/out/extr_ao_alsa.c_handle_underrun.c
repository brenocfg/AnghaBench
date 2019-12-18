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
struct priv {int /*<<< orphan*/  alsa; int /*<<< orphan*/  final_chunk_written; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 int /*<<< orphan*/  ao_underrun_event (struct ao*) ; 
 int snd_pcm_prepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_underrun(struct ao *ao)
{
    struct priv *p = ao->priv;

    if (!p->final_chunk_written) {
        ao_underrun_event(ao);

        int err = snd_pcm_prepare(p->alsa);
        CHECK_ALSA_ERROR("pcm prepare error");
    alsa_error: ;
    }
}