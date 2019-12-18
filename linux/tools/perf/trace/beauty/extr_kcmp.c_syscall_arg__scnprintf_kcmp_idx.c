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
struct syscall_arg {unsigned long val; int idx; int /*<<< orphan*/  trace; } ;
typedef  void* pid_t ;

/* Variables and functions */
 int KCMP_FILE ; 
 size_t pid__scnprintf_fd (int /*<<< orphan*/ ,void*,unsigned long,char*,size_t) ; 
 size_t syscall_arg__scnprintf_long (char*,size_t,struct syscall_arg*) ; 
 void* syscall_arg__val (struct syscall_arg*,int) ; 

size_t syscall_arg__scnprintf_kcmp_idx(char *bf, size_t size, struct syscall_arg *arg)
{
	unsigned long fd = arg->val;
	int type = syscall_arg__val(arg, 2);
	pid_t pid;

	if (type != KCMP_FILE)
		return syscall_arg__scnprintf_long(bf, size, arg);

	pid = syscall_arg__val(arg, arg->idx == 3 ? 0 : 1); /* idx1 -> pid1, idx2 -> pid2 */
	return pid__scnprintf_fd(arg->trace, pid, fd, bf, size);
}