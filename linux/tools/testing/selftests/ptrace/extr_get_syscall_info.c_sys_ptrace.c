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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_ptrace ; 
 long syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static long
sys_ptrace(int request, pid_t pid, unsigned long addr, unsigned long data)
{
	return syscall(__NR_ptrace, request, pid, addr, data);
}