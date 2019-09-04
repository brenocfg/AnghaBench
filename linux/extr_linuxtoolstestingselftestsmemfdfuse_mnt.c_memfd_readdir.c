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
struct fuse_file_info {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  (* fuse_fill_dir_t ) (void*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int ENOENT ; 
 char* memfd_path ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int memfd_readdir(const char *path,
			 void *buf,
			 fuse_fill_dir_t filler,
			 off_t offset,
			 struct fuse_file_info *fi)
{
	if (strcmp(path, "/"))
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, memfd_path + 1, NULL, 0);

	return 0;
}