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
struct TYPE_2__ {int /*<<< orphan*/ * lock; } ;
typedef  int /*<<< orphan*/  LWLock ;

/* Variables and functions */
 TYPE_1__* held_lwlocks ; 
 int num_held_lwlocks ; 

bool
LWLockHeldByMe(LWLock *l)
{
	int			i;

	for (i = 0; i < num_held_lwlocks; i++)
	{
		if (held_lwlocks[i].lock == l)
			return true;
	}
	return false;
}