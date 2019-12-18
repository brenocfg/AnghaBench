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
struct syscall_arg {int dummy; } ;

/* Variables and functions */
 size_t __syscall_arg__scnprintf_strarray (char*,size_t,char*,struct syscall_arg*) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_strarray(char *bf, size_t size,
					      struct syscall_arg *arg)
{
	return __syscall_arg__scnprintf_strarray(bf, size, "%d", arg);
}