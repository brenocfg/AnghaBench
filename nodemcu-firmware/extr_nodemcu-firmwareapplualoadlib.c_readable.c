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
 int /*<<< orphan*/  vfs_close (int) ; 
 int vfs_open (char const*,char*) ; 

__attribute__((used)) static int readable (const char *filename) {
  int f = vfs_open(filename, "r");  /* try to open file */
  if (!f) return 0;  /* open failed */
  vfs_close(f);
  return 1;
}