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
struct syscall_arg {int val; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 size_t scnprintf (char*,size_t,char*) ; 
 size_t syscall_arg__scnprintf_fd (char*,size_t,struct syscall_arg*) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_fd_at(char *bf, size_t size,
					   struct syscall_arg *arg)
{
	int fd = arg->val;

	if (fd == AT_FDCWD)
		return scnprintf(bf, size, "CWD");

	return syscall_arg__scnprintf_fd(bf, size, arg);
}