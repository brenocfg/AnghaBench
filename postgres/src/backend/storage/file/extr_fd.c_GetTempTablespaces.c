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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TempTablespacesAreSet () ; 
 int numTempTableSpaces ; 
 int /*<<< orphan*/ * tempTableSpaces ; 

int
GetTempTablespaces(Oid *tableSpaces, int numSpaces)
{
	int			i;

	Assert(TempTablespacesAreSet());
	for (i = 0; i < numTempTableSpaces && i < numSpaces; ++i)
		tableSpaces[i] = tempTableSpaces[i];

	return i;
}