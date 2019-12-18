#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ntablespaces; int /*<<< orphan*/ * tablespaces; } ;
typedef  TYPE_1__ SharedFileSet ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PathNameDeleteTemporaryDir (char*) ; 
 int /*<<< orphan*/  SharedFileSetPath (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
SharedFileSetDeleteAll(SharedFileSet *fileset)
{
	char		dirpath[MAXPGPATH];
	int			i;

	/*
	 * Delete the directory we created in each tablespace.  Doesn't fail
	 * because we use this in error cleanup paths, but can generate LOG
	 * message on IO error.
	 */
	for (i = 0; i < fileset->ntablespaces; ++i)
	{
		SharedFileSetPath(dirpath, fileset, fileset->tablespaces[i]);
		PathNameDeleteTemporaryDir(dirpath);
	}
}