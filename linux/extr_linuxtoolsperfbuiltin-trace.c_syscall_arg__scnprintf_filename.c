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
struct syscall_arg {unsigned long val; int /*<<< orphan*/  thread; TYPE_1__* trace; } ;
struct TYPE_2__ {int /*<<< orphan*/  vfs_getname; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,unsigned long) ; 
 int /*<<< orphan*/  thread__set_filename_pos (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_filename(char *bf, size_t size,
					      struct syscall_arg *arg)
{
	unsigned long ptr = arg->val;

	if (!arg->trace->vfs_getname)
		return scnprintf(bf, size, "%#x", ptr);

	thread__set_filename_pos(arg->thread, bf, ptr);
	return 0;
}