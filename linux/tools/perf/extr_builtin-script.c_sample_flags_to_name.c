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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {char const* name; scalar_t__ flags; } ;

/* Variables and functions */
 TYPE_1__* sample_flags ; 

__attribute__((used)) static const char *sample_flags_to_name(u32 flags)
{
	int i;

	for (i = 0; sample_flags[i].name ; i++) {
		if (sample_flags[i].flags == flags)
			return sample_flags[i].name;
	}

	return NULL;
}