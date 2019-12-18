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
struct priv {int device_failed; int audio_fd; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDCTL_DSP_RESET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_device(struct ao *ao)
{
    struct priv *p = ao->priv;
    p->device_failed = false;
    if (p->audio_fd == -1)
        return;
#if defined(SNDCTL_DSP_RESET)
    ioctl(p->audio_fd, SNDCTL_DSP_RESET, NULL);
#endif
    close(p->audio_fd);
    p->audio_fd = -1;
}