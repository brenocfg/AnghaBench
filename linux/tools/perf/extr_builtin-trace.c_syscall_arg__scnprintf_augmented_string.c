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
struct TYPE_2__ {int size; struct augmented_arg* args; } ;
struct syscall_arg {TYPE_1__ augmented; } ;
struct augmented_arg {int size; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_augmented_string(struct syscall_arg *arg, char *bf, size_t size)
{
	struct augmented_arg *augmented_arg = arg->augmented.args;
	size_t printed = scnprintf(bf, size, "\"%.*s\"", augmented_arg->size, augmented_arg->value);
	/*
	 * So that the next arg with a payload can consume its augmented arg, i.e. for rename* syscalls
	 * we would have two strings, each prefixed by its size.
	 */
	int consumed = sizeof(*augmented_arg) + augmented_arg->size;

	arg->augmented.args = ((void *)arg->augmented.args) + consumed;
	arg->augmented.size -= consumed;

	return printed;
}