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
struct mp_hwdec_devices {int dummy; } ;
struct gl_video {int hwdec_interop_loading_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  load_add_hwdec (struct gl_video*,struct mp_hwdec_devices*,scalar_t__,int) ; 
 scalar_t__* ra_hwdec_drivers ; 

void gl_video_load_hwdecs_all(struct gl_video *p, struct mp_hwdec_devices *devs)
{
    if (!p->hwdec_interop_loading_done) {
        for (int n = 0; ra_hwdec_drivers[n]; n++)
            load_add_hwdec(p, devs, ra_hwdec_drivers[n], true);
        p->hwdec_interop_loading_done = true;
    }
}