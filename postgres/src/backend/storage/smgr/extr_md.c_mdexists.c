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
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  int /*<<< orphan*/  ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENSION_RETURN_NULL ; 
 int /*<<< orphan*/  mdclose (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mdopenfork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
mdexists(SMgrRelation reln, ForkNumber forkNum)
{
	/*
	 * Close it first, to ensure that we notice if the fork has been unlinked
	 * since we opened it.
	 */
	mdclose(reln, forkNum);

	return (mdopenfork(reln, forkNum, EXTENSION_RETURN_NULL) != NULL);
}