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
typedef  scalar_t__ TimeoutId ;
struct TYPE_2__ {scalar_t__ index; } ;

/* Variables and functions */
 TYPE_1__** active_timeouts ; 
 int num_active_timeouts ; 

__attribute__((used)) static int
find_active_timeout(TimeoutId id)
{
	int			i;

	for (i = 0; i < num_active_timeouts; i++)
	{
		if (active_timeouts[i]->index == id)
			return i;
	}

	return -1;
}