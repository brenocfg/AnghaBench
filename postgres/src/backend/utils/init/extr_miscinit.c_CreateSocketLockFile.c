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
typedef  int /*<<< orphan*/  lockfile ;

/* Variables and functions */
 int /*<<< orphan*/  CreateLockFile (char*,int,char const*,int,char const*) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

void
CreateSocketLockFile(const char *socketfile, bool amPostmaster,
					 const char *socketDir)
{
	char		lockfile[MAXPGPATH];

	snprintf(lockfile, sizeof(lockfile), "%s.lock", socketfile);
	CreateLockFile(lockfile, amPostmaster, socketDir, false, socketfile);
}