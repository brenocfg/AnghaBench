#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ args; } ;
struct syscall_arg {unsigned long val; int /*<<< orphan*/  thread; TYPE_2__* trace; TYPE_1__ augmented; } ;
struct TYPE_4__ {int /*<<< orphan*/  vfs_getname; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,unsigned long) ; 
 size_t syscall_arg__scnprintf_augmented_string (struct syscall_arg*,char*,size_t) ; 
 int /*<<< orphan*/  thread__set_filename_pos (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_filename(char *bf, size_t size,
					      struct syscall_arg *arg)
{
	unsigned long ptr = arg->val;

	if (arg->augmented.args)
		return syscall_arg__scnprintf_augmented_string(arg, bf, size);

	if (!arg->trace->vfs_getname)
		return scnprintf(bf, size, "%#x", ptr);

	thread__set_filename_pos(arg->thread, bf, ptr);
	return 0;
}