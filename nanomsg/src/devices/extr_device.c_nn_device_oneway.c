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
struct nn_device_recipe {int dummy; } ;

/* Variables and functions */
 int nn_device_mvmsg (struct nn_device_recipe*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 

int nn_device_oneway (struct nn_device_recipe *device, int s1, int s2)
{
    int rc;

    while (1) {
        rc = nn_device_mvmsg (device, s1, s2, 0);
        if (nn_slow (rc < 0))
            return -1;
    }
}