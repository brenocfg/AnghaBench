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
 int getxattr (int /*<<< orphan*/ ,char const*,char*,size_t) ; 

__attribute__((used)) static int pifs_getxattr(const char *path, const char *name, char *value,
                         size_t size)
{
  FULL_PATH(path);
  int ret = getxattr(full_path, name, value, size);
  return ret == -1 ? -errno : ret;
}