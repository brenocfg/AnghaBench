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
struct priv {scalar_t__ prepause_samples; scalar_t__ audio_end; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_play_silence (struct ao*,scalar_t__) ; 

__attribute__((used)) static void audio_resume(struct ao *ao)
{
    struct priv *p = ao->priv;
    p->audio_end = 0;
    if (p->prepause_samples > 0)
        ao_play_silence(ao, p->prepause_samples);
}