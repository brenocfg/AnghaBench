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
 int check_execveat_invoked_rc (int,char const*,int,int,int) ; 

__attribute__((used)) static int check_execveat(int fd, const char *path, int flags)
{
	return check_execveat_invoked_rc(fd, path, flags, 99, 99);
}