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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_PATH (char const*) ; 
 int S_IFDIR ; 
 int errno ; 
 int /*<<< orphan*/  full_path ; 
 int mkdir (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pifs_mkdir(const char *path, mode_t mode)
{
  FULL_PATH(path);
  int ret = mkdir(full_path, mode | S_IFDIR);
  return ret == -1 ? -errno : ret;
}