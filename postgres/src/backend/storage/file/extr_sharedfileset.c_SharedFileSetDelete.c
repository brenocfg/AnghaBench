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
typedef  int /*<<< orphan*/  SharedFileSet ;

/* Variables and functions */
 int MAXPGPATH ; 
 int PathNameDeleteTemporaryFile (char*,int) ; 
 int /*<<< orphan*/  SharedFilePath (char*,int /*<<< orphan*/ *,char const*) ; 

bool
SharedFileSetDelete(SharedFileSet *fileset, const char *name,
					bool error_on_failure)
{
	char		path[MAXPGPATH];

	SharedFilePath(path, fileset, name);

	return PathNameDeleteTemporaryFile(path, error_on_failure);
}