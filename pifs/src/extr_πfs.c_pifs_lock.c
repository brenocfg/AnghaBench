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
struct fuse_file_info {int /*<<< orphan*/  fh; } ;
struct flock {int dummy; } ;

/* Variables and functions */
 int errno ; 
 int fcntl (int /*<<< orphan*/ ,int,struct flock*) ; 

__attribute__((used)) static int pifs_lock(const char *path, struct fuse_file_info *info, int cmd,
                     struct flock *lock)
{
  int ret = fcntl(info->fh, cmd, lock);
  return ret == -1 ? -errno : ret;
}