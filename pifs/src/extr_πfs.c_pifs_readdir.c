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
struct fuse_file_info {scalar_t__ fh; } ;
struct dirent {int /*<<< orphan*/  d_off; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int (* fuse_fill_dir_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int errno ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seekdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pifs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *info)
{
  DIR *dir = (DIR *) info->fh;
  if (offset) {
    seekdir(dir, offset);
  }

  int ret;
  do {
    errno = 0;
    struct dirent *de = readdir(dir);
    if (!de) { 
      if (errno) {
        return -errno;
      } else {
        break;
      }
    }

    ret = filler(buf, de->d_name, NULL, de->d_off);
  } while (ret == 0);

  return 0;
}