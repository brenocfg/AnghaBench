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
typedef  size_t __u32 ;
struct TYPE_2__ {unsigned int sick_mask; } ;

/* Variables and functions */
 TYPE_1__* type_to_health_flag ; 

unsigned int
xchk_health_mask_for_scrub_type(
	__u32			scrub_type)
{
	return type_to_health_flag[scrub_type].sick_mask;
}