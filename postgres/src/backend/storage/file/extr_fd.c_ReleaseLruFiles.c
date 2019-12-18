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

/* Variables and functions */
 int /*<<< orphan*/  ReleaseLruFile () ; 
 scalar_t__ max_safe_fds ; 
 scalar_t__ nfile ; 
 scalar_t__ numAllocatedDescs ; 

__attribute__((used)) static void
ReleaseLruFiles(void)
{
	while (nfile + numAllocatedDescs >= max_safe_fds)
	{
		if (!ReleaseLruFile())
			break;
	}
}