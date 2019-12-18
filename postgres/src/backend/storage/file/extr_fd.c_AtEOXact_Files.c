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
 int /*<<< orphan*/  CleanupTempFiles (int,int) ; 
 int numTempTableSpaces ; 
 int /*<<< orphan*/ * tempTableSpaces ; 

void
AtEOXact_Files(bool isCommit)
{
	CleanupTempFiles(isCommit, false);
	tempTableSpaces = NULL;
	numTempTableSpaces = -1;
}