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
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ File ;

/* Variables and functions */
 int /*<<< orphan*/  ChooseTablespace (int /*<<< orphan*/ *,char const*) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PathNameCreateTemporaryDir (char*,char*) ; 
 scalar_t__ PathNameCreateTemporaryFile (char*,int) ; 
 int /*<<< orphan*/  SharedFilePath (char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SharedFileSetPath (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TempTablespacePath (char*,int /*<<< orphan*/ ) ; 

File
SharedFileSetCreate(SharedFileSet *fileset, const char *name)
{
	char		path[MAXPGPATH];
	File		file;

	SharedFilePath(path, fileset, name);
	file = PathNameCreateTemporaryFile(path, false);

	/* If we failed, see if we need to create the directory on demand. */
	if (file <= 0)
	{
		char		tempdirpath[MAXPGPATH];
		char		filesetpath[MAXPGPATH];
		Oid			tablespace = ChooseTablespace(fileset, name);

		TempTablespacePath(tempdirpath, tablespace);
		SharedFileSetPath(filesetpath, fileset, tablespace);
		PathNameCreateTemporaryDir(tempdirpath, filesetpath);
		file = PathNameCreateTemporaryFile(path, true);
	}

	return file;
}