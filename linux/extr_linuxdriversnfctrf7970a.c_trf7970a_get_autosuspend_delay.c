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
struct device_node {int dummy; } ;

/* Variables and functions */
 int TRF7970A_AUTOSUSPEND_DELAY ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int trf7970a_get_autosuspend_delay(struct device_node *np)
{
	int autosuspend_delay, ret;

	ret = of_property_read_u32(np, "autosuspend-delay", &autosuspend_delay);
	if (ret)
		autosuspend_delay = TRF7970A_AUTOSUSPEND_DELAY;

	return autosuspend_delay;
}