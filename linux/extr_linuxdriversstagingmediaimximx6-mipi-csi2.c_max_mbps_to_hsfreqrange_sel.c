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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ max_mbps; int hsfreqrange_sel; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* hsfreq_map ; 

__attribute__((used)) static int max_mbps_to_hsfreqrange_sel(u32 max_mbps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(hsfreq_map); i++)
		if (hsfreq_map[i].max_mbps > max_mbps)
			return hsfreq_map[i].hsfreqrange_sel;

	return -EINVAL;
}