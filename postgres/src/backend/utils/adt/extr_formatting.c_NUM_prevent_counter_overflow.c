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
 int INT_MAX ; 
 TYPE_1__** NUMCache ; 
 int NUMCounter ; 
 int n_NUMCache ; 

__attribute__((used)) static inline void
NUM_prevent_counter_overflow(void)
{
	if (NUMCounter >= (INT_MAX - 1))
	{
		for (int i = 0; i < n_NUMCache; i++)
			NUMCache[i]->age >>= 1;
		NUMCounter >>= 1;
	}
}