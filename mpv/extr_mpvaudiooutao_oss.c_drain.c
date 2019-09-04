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
struct ao {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void drain(struct ao *ao)
{
#ifdef SNDCTL_DSP_SYNC
    struct priv *p = ao->priv;
    // to get the buffer played
    if (p->audio_fd != -1)
        ioctl(p->audio_fd, SNDCTL_DSP_SYNC, NULL);
#endif
}