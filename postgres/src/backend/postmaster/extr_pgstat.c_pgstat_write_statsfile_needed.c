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
 scalar_t__ NIL ; 
 scalar_t__ pending_write_requests ; 

__attribute__((used)) static bool
pgstat_write_statsfile_needed(void)
{
	if (pending_write_requests != NIL)
		return true;

	/* Everything was written recently */
	return false;
}