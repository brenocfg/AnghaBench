#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ args; } ;
struct syscall_arg {int /*<<< orphan*/  val; TYPE_1__ augmented; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 size_t syscall_arg__scnprintf_augmented_sockaddr (struct syscall_arg*,char*,size_t) ; 

size_t syscall_arg__scnprintf_sockaddr(char *bf, size_t size, struct syscall_arg *arg)
{
	if (arg->augmented.args)
		return syscall_arg__scnprintf_augmented_sockaddr(arg, bf, size);

	return scnprintf(bf, size, "%#x", arg->val);
}