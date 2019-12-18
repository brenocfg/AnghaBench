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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,int /*<<< orphan*/ ) ; 
 char* DataDir ; 
 int /*<<< orphan*/  ExitPostmaster (int) ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_stderr (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
checkControlFile(void)
{
	char		path[MAXPGPATH];
	FILE	   *fp;

	snprintf(path, sizeof(path), "%s/global/pg_control", DataDir);

	fp = AllocateFile(path, PG_BINARY_R);
	if (fp == NULL)
	{
		write_stderr("%s: could not find the database system\n"
					 "Expected to find it in the directory \"%s\",\n"
					 "but could not open file \"%s\": %s\n",
					 progname, DataDir, path, strerror(errno));
		ExitPostmaster(2);
	}
	FreeFile(fp);
}