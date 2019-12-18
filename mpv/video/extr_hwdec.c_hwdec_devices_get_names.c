#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_hwdec_devices {int num_hwctxs; TYPE_1__** hwctxs; } ;
struct TYPE_2__ {char* driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ta_xstrdup_append (char**,char*) ; 

char *hwdec_devices_get_names(struct mp_hwdec_devices *devs)
{
    char *res = NULL;
    for (int n = 0; n < devs->num_hwctxs; n++) {
        if (res)
            ta_xstrdup_append(&res, ",");
        ta_xstrdup_append(&res, devs->hwctxs[n]->driver_name);
    }
    return res;
}