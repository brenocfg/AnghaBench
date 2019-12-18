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
struct syscall_arg {int /*<<< orphan*/  val; int /*<<< orphan*/  show_string_prefix; int /*<<< orphan*/  parm; } ;

/* Variables and functions */
 size_t strarrays__scnprintf (int /*<<< orphan*/ ,char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_strarrays(char *bf, size_t size,
					struct syscall_arg *arg)
{
	return strarrays__scnprintf(arg->parm, bf, size, "%d", arg->show_string_prefix, arg->val);
}