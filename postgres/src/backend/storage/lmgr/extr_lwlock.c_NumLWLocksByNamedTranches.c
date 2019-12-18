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
struct TYPE_2__ {scalar_t__ num_lwlocks; } ;

/* Variables and functions */
 TYPE_1__* NamedLWLockTrancheRequestArray ; 
 int NamedLWLockTrancheRequests ; 

__attribute__((used)) static int
NumLWLocksByNamedTranches(void)
{
	int			numLocks = 0;
	int			i;

	for (i = 0; i < NamedLWLockTrancheRequests; i++)
		numLocks += NamedLWLockTrancheRequestArray[i].num_lwlocks;

	return numLocks;
}