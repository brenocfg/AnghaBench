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
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MAX_TIME_PRECISION ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,char*,...) ; 

int32
anytime_typmod_check(bool istz, int32 typmod)
{
	if (typmod < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("TIME(%d)%s precision must not be negative",
						typmod, (istz ? " WITH TIME ZONE" : ""))));
	if (typmod > MAX_TIME_PRECISION)
	{
		ereport(WARNING,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("TIME(%d)%s precision reduced to maximum allowed, %d",
						typmod, (istz ? " WITH TIME ZONE" : ""),
						MAX_TIME_PRECISION)));
		typmod = MAX_TIME_PRECISION;
	}

	return typmod;
}