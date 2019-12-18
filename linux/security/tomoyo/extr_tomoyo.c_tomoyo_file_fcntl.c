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
struct file {unsigned long f_flags; int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 unsigned int F_SETFL ; 
 unsigned long O_APPEND ; 
 unsigned long O_WRONLY ; 
 int tomoyo_check_open_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tomoyo_domain () ; 

__attribute__((used)) static int tomoyo_file_fcntl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	if (!(cmd == F_SETFL && ((arg ^ file->f_flags) & O_APPEND)))
		return 0;
	return tomoyo_check_open_permission(tomoyo_domain(), &file->f_path,
					    O_WRONLY | (arg & O_APPEND));
}