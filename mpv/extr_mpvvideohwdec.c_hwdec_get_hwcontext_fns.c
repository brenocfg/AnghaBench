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
struct hwcontext_fns {int av_hwdevice_type; } ;

/* Variables and functions */
 struct hwcontext_fns const** hwcontext_fns ; 

const struct hwcontext_fns *hwdec_get_hwcontext_fns(int av_hwdevice_type)
{
    for (int n = 0; hwcontext_fns[n]; n++) {
        if (hwcontext_fns[n]->av_hwdevice_type == av_hwdevice_type)
            return hwcontext_fns[n];
    }
    return NULL;
}