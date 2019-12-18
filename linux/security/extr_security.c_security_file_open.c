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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_OPEN ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  file_open ; 
 int fsnotify_perm (struct file*,int /*<<< orphan*/ ) ; 

int security_file_open(struct file *file)
{
	int ret;

	ret = call_int_hook(file_open, 0, file);
	if (ret)
		return ret;

	return fsnotify_perm(file, MAY_OPEN);
}