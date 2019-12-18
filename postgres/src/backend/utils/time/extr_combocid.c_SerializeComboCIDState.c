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
typedef  int Size ;
typedef  int /*<<< orphan*/  ComboCidKeyData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  comboCids ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int usedComboCids ; 

void
SerializeComboCIDState(Size maxsize, char *start_address)
{
	char	   *endptr;

	/* First, we store the number of currently-existing ComboCIDs. */
	*(int *) start_address = usedComboCids;

	/* If maxsize is too small, throw an error. */
	endptr = start_address + sizeof(int) +
		(sizeof(ComboCidKeyData) * usedComboCids);
	if (endptr < start_address || endptr > start_address + maxsize)
		elog(ERROR, "not enough space to serialize ComboCID state");

	/* Now, copy the actual cmin/cmax pairs. */
	if (usedComboCids > 0)
		memcpy(start_address + sizeof(int), comboCids,
			   (sizeof(ComboCidKeyData) * usedComboCids));
}