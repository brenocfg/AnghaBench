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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ nextTempTableSpace ; 
 scalar_t__ numTempTableSpaces ; 
 int /*<<< orphan*/ * tempTableSpaces ; 

Oid
GetNextTempTableSpace(void)
{
	if (numTempTableSpaces > 0)
	{
		/* Advance nextTempTableSpace counter with wraparound */
		if (++nextTempTableSpace >= numTempTableSpaces)
			nextTempTableSpace = 0;
		return tempTableSpaces[nextTempTableSpace];
	}
	return InvalidOid;
}