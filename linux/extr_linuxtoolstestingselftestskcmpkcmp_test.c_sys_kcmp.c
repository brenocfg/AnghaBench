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
 int /*<<< orphan*/  __NR_kcmp ; 
 long syscall (int /*<<< orphan*/ ,int,int,int,unsigned long,unsigned long) ; 

__attribute__((used)) static long sys_kcmp(int pid1, int pid2, int type, unsigned long fd1, unsigned long fd2)
{
	return syscall(__NR_kcmp, pid1, pid2, type, fd1, fd2);
}