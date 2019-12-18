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
 int nn_device_entry (struct nn_device_recipe*,int,int,int) ; 

int nn_custom_device(struct nn_device_recipe *device, int s1, int s2,
    int flags)
{
    return nn_device_entry (device, s1, s2, flags);
}