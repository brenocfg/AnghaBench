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
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_NOCMTIME ; 
 int file_remove_privs (struct file*) ; 
 int file_update_time (struct file*) ; 
 scalar_t__ unlikely (int) ; 

int file_modified(struct file *file)
{
	int err;

	/*
	 * Clear the security bits if the process is not being run by root.
	 * This keeps people from modifying setuid and setgid binaries.
	 */
	err = file_remove_privs(file);
	if (err)
		return err;

	if (unlikely(file->f_mode & FMODE_NOCMTIME))
		return 0;

	return file_update_time(file);
}