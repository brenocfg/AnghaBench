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
typedef  int /*<<< orphan*/  File ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PathNameOpenTemporaryFile (char*) ; 
 int /*<<< orphan*/  SharedFilePath (char*,int /*<<< orphan*/ *,char const*) ; 

File
SharedFileSetOpen(SharedFileSet *fileset, const char *name)
{
	char		path[MAXPGPATH];
	File		file;

	SharedFilePath(path, fileset, name);
	file = PathNameOpenTemporaryFile(path);

	return file;
}