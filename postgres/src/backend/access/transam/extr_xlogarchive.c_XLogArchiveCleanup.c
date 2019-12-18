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
 int MAXPGPATH ; 
 int /*<<< orphan*/  StatusFilePath (char*,char const*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
XLogArchiveCleanup(const char *xlog)
{
	char		archiveStatusPath[MAXPGPATH];

	/* Remove the .done file */
	StatusFilePath(archiveStatusPath, xlog, ".done");
	unlink(archiveStatusPath);
	/* should we complain about failure? */

	/* Remove the .ready file if present --- normally it shouldn't be */
	StatusFilePath(archiveStatusPath, xlog, ".ready");
	unlink(archiveStatusPath);
	/* should we complain about failure? */
}