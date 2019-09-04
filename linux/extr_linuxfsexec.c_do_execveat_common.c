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
struct user_arg_ptr {int dummy; } ;
struct filename {int dummy; } ;

/* Variables and functions */
 int __do_execve_file (int,struct filename*,struct user_arg_ptr,struct user_arg_ptr,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_execveat_common(int fd, struct filename *filename,
			      struct user_arg_ptr argv,
			      struct user_arg_ptr envp,
			      int flags)
{
	return __do_execve_file(fd, filename, argv, envp, flags, NULL);
}