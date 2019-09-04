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
struct TYPE_2__ {scalar_t__ pfkey_supported; scalar_t__ available; } ;

/* Variables and functions */
 int aalg_entries () ; 
 TYPE_1__* aalg_list ; 

int xfrm_count_pfkey_auth_supported(void)
{
	int i, n;

	for (i = 0, n = 0; i < aalg_entries(); i++)
		if (aalg_list[i].available && aalg_list[i].pfkey_supported)
			n++;
	return n;
}