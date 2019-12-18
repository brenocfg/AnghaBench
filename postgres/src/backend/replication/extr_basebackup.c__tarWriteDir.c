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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  int64 ;

/* Variables and functions */
 int S_IFDIR ; 
 scalar_t__ S_ISLNK (int) ; 
 int /*<<< orphan*/  _tarWriteHeader (char const*,int /*<<< orphan*/ *,struct stat*,int) ; 
 int pg_dir_create_mode ; 
 scalar_t__ pgwin32_is_junction (char const*) ; 

__attribute__((used)) static int64
_tarWriteDir(const char *pathbuf, int basepathlen, struct stat *statbuf,
			 bool sizeonly)
{
	/* If symlink, write it as a directory anyway */
#ifndef WIN32
	if (S_ISLNK(statbuf->st_mode))
#else
	if (pgwin32_is_junction(pathbuf))
#endif
		statbuf->st_mode = S_IFDIR | pg_dir_create_mode;

	return _tarWriteHeader(pathbuf + basepathlen + 1, NULL, statbuf, sizeonly);
}