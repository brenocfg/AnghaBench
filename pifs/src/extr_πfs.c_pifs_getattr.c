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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_PATH (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  full_path ; 
 int lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int pifs_getattr(const char *path, struct stat *buf)
{
  FULL_PATH(path);
  int ret = lstat(full_path, buf);
  buf->st_size /= 2;
  return ret == -1 ? -errno : ret;
}