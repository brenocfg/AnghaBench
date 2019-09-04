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
struct file {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_TYPE_IOCTL ; 
 int tomoyo_path_number_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int tomoyo_file_ioctl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	return tomoyo_path_number_perm(TOMOYO_TYPE_IOCTL, &file->f_path, cmd);
}