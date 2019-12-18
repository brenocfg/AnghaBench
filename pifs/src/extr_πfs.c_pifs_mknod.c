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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_PATH (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  full_path ; 
 int mknod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pifs_mknod(const char *path, mode_t mode, dev_t dev)
{
  FULL_PATH(path);
  int ret = mknod(full_path, mode, dev);
  return ret == -1 ? -errno : ret;
}