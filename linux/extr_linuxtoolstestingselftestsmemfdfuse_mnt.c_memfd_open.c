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
struct fuse_file_info {int flags; int direct_io; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  memfd_path ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memfd_open(const char *path, struct fuse_file_info *fi)
{
	if (strcmp(path, memfd_path))
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	/* force direct-IO */
	fi->direct_io = 1;

	return 0;
}