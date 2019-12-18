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
typedef  scalar_t__ uint64_t ;
struct fuse_file_info {scalar_t__ fh; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_PATH (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  full_path ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pifs_opendir(const char *path, struct fuse_file_info *info)
{
  FULL_PATH(path);
  DIR *dir = opendir(full_path);
  info->fh = (uint64_t) dir;
  return !dir ? -errno : 0;
}