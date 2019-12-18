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
 int readlink (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int pifs_readlink(const char *path, char *buf, size_t bufsiz)
{
  FULL_PATH(path);
  int ret = readlink(full_path, buf, bufsiz - 1);
  if (ret == -1) {
    return -errno;
  }

  buf[ret] = '\0';
  return 0;
}