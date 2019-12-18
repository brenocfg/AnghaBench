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
struct syscall_arg {unsigned long val; int /*<<< orphan*/  show_string_prefix; int /*<<< orphan*/  thread; } ;
struct file {scalar_t__ dev_maj; } ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_MAJOR ; 
 int /*<<< orphan*/  _IOC_DIR (unsigned long) ; 
 int /*<<< orphan*/  _IOC_NR (unsigned long) ; 
 size_t ioctl__scnprintf_cmd (unsigned long,char*,size_t,int /*<<< orphan*/ ) ; 
 size_t ioctl__scnprintf_usbdevfs_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int syscall_arg__val (struct syscall_arg*,int /*<<< orphan*/ ) ; 
 struct file* thread__files_entry (int /*<<< orphan*/ ,int) ; 

size_t syscall_arg__scnprintf_ioctl_cmd(char *bf, size_t size, struct syscall_arg *arg)
{
	unsigned long cmd = arg->val;
	int fd = syscall_arg__val(arg, 0);
	struct file *file = thread__files_entry(arg->thread, fd);

	if (file != NULL) {
		if (file->dev_maj == USB_DEVICE_MAJOR)
			return ioctl__scnprintf_usbdevfs_cmd(_IOC_NR(cmd), _IOC_DIR(cmd), bf, size);
	}

	return ioctl__scnprintf_cmd(cmd, bf, size, arg->show_string_prefix);
}