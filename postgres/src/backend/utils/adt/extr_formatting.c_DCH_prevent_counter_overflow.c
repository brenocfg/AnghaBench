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
struct TYPE_2__ {int age; } ;

/* Variables and functions */
 TYPE_1__** DCHCache ; 
 int DCHCounter ; 
 int INT_MAX ; 
 int n_DCHCache ; 

__attribute__((used)) static inline void
DCH_prevent_counter_overflow(void)
{
	if (DCHCounter >= (INT_MAX - 1))
	{
		for (int i = 0; i < n_DCHCache; i++)
			DCHCache[i]->age >>= 1;
		DCHCounter >>= 1;
	}
}