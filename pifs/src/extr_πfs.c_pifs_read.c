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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 scalar_t__ get_byte (short) ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,short*,int) ; 

__attribute__((used)) static int pifs_read(const char *path, char *buf, size_t count, off_t offset,
                     struct fuse_file_info *info)
{
  int ret = lseek(info->fh, offset * 2, SEEK_SET);
  if (ret == -1) {
    return -errno;
  }

  for (size_t i = 0; i < count; i++) {
    short index;
    ret = read(info->fh, &index, sizeof index);
    if (ret == -1) {
      return -errno;
    } else if (ret == 0) {
      return i;
    }
    *buf = (char) get_byte(index);
    buf++;
  }

  return count;
}