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
typedef  int /*<<< orphan*/  ExtensionMemberId ;

/* Variables and functions */
 int /*<<< orphan*/  ExtensionMemberIdCompare ; 
 int /*<<< orphan*/ * extmembers ; 
 int numextmembers ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 

void
setExtensionMembership(ExtensionMemberId *extmems, int nextmems)
{
	/* Sort array in preparation for binary searches */
	if (nextmems > 1)
		qsort((void *) extmems, nextmems, sizeof(ExtensionMemberId),
			  ExtensionMemberIdCompare);
	/* And save */
	extmembers = extmems;
	numextmembers = nextmems;
}