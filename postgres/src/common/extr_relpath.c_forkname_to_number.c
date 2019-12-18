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
typedef  size_t ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 size_t InvalidForkNumber ; 
 size_t MAX_FORKNUM ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * forkNames ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

ForkNumber
forkname_to_number(const char *forkName)
{
	ForkNumber	forkNum;

	for (forkNum = 0; forkNum <= MAX_FORKNUM; forkNum++)
		if (strcmp(forkNames[forkNum], forkName) == 0)
			return forkNum;

#ifndef FRONTEND
	ereport(ERROR,
			(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
			 errmsg("invalid fork name"),
			 errhint("Valid fork names are \"main\", \"fsm\", "
					 "\"vm\", and \"init\".")));
#endif

	return InvalidForkNumber;
}