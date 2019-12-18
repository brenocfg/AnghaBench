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
struct statvfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_PATH (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  full_path ; 
 int statvfs (int /*<<< orphan*/ ,struct statvfs*) ; 

__attribute__((used)) static int pifs_statfs(const char *path, struct statvfs *buf)
{
  FULL_PATH(path);
  int ret = statvfs(full_path, buf);
  return ret == -1 ? -errno : ret;
}