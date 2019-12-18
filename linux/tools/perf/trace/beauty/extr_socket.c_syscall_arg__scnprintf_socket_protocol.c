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
struct syscall_arg {int /*<<< orphan*/  show_string_prefix; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 size_t socket__scnprintf_ipproto (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 size_t syscall_arg__scnprintf_int (char*,size_t,struct syscall_arg*) ; 
 int syscall_arg__val (struct syscall_arg*,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_socket_protocol(char *bf, size_t size, struct syscall_arg *arg)
{
	int domain = syscall_arg__val(arg, 0);

	if (domain == AF_INET || domain == AF_INET6)
		return socket__scnprintf_ipproto(arg->val, bf, size, arg->show_string_prefix);

	return syscall_arg__scnprintf_int(bf, size, arg);
}