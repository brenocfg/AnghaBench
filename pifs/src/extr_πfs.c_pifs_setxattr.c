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

/* Variables and functions */
 int /*<<< orphan*/  FULL_PATH (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  full_path ; 
 int setxattr (int /*<<< orphan*/ ,char const*,char const*,size_t,int) ; 

__attribute__((used)) static int pifs_setxattr(const char *path, const char *name, const char *value,
                         size_t size, int flags)
{
  FULL_PATH(path);
  int ret = setxattr(full_path, name, value, size, flags);
  return ret == -1 ? -errno : ret;
}