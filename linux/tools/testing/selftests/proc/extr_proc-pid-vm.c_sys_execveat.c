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
 int /*<<< orphan*/  SYS_execveat ; 
 long syscall (int /*<<< orphan*/ ,int,char const*,char**,char**,int) ; 

__attribute__((used)) static inline long sys_execveat(int dirfd, const char *pathname, char **argv, char **envp, int flags)
{
	return syscall(SYS_execveat, dirfd, pathname, argv, envp, flags);
}