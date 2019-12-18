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
struct autofs_sb_info {int dummy; } ;
struct autofs_dev_ioctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  autofs_catatonic_mode (struct autofs_sb_info*) ; 

__attribute__((used)) static int autofs_dev_ioctl_catatonic(struct file *fp,
				      struct autofs_sb_info *sbi,
				      struct autofs_dev_ioctl *param)
{
	autofs_catatonic_mode(sbi);
	return 0;
}