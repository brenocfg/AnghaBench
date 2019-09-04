#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {scalar_t__ audio_fd; double audio_end; int audio_delay_method; double buffersize; } ;
struct ao {scalar_t__ bps; struct priv* priv; } ;
struct TYPE_3__ {double bytes; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ audio_buf_info ;

/* Variables and functions */
 int /*<<< orphan*/  SNDCTL_DSP_GETOSPACE ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 double mp_time_sec () ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct priv *p = ao->priv;
    if (p->audio_fd < 0) {
        double rest = p->audio_end - mp_time_sec();
        if (rest > 0)
            return rest;
        return 0;
    }
    /* Calculate how many bytes/second is sent out */
    if (p->audio_delay_method == 2) {
#ifdef SNDCTL_DSP_GETODELAY
        int r = 0;
        if (ioctl(p->audio_fd, SNDCTL_DSP_GETODELAY, &r) != -1)
            return r / (double)ao->bps;
#endif
        p->audio_delay_method = 1; // fallback if not supported
    }
    if (p->audio_delay_method == 1) {
        audio_buf_info zz = {0};
        if (ioctl(p->audio_fd, SNDCTL_DSP_GETOSPACE, &zz) != -1) {
            return (p->buffersize - zz.bytes) / (double)ao->bps;
        }
        p->audio_delay_method = 0; // fallback if not supported
    }
    return p->buffersize / (double)ao->bps;
}