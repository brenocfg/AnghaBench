#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  F_NORMAL ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int TRUE ; 
 TYPE_1__* dents ; 
 int /*<<< orphan*/  mkpath (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ndents ; 
 int /*<<< orphan*/  printwait (char*,int*) ; 
 int /*<<< orphan*/  spawn (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool execute_file(int cur, char *path, char *newpath, int *presel)
{
	if (!ndents)
		return FALSE;

	/* Check if this is a directory */
	if (!S_ISREG(dents[cur].mode)) {
		printwait("not regular file", presel);
		return FALSE;
	}

	/* Check if file is executable */
	if (!(dents[cur].mode & 0100)) {
		printwait("permission denied", presel);
		return FALSE;
	}

	mkpath(path, dents[cur].name, newpath);
	spawn(newpath, NULL, NULL, path, F_NORMAL);

	return TRUE;
}