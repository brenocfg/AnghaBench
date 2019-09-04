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
struct file {int dummy; } ;
struct autofs_sb_info {unsigned long exp_timeout; } ;
struct TYPE_2__ {unsigned long timeout; } ;
struct autofs_dev_ioctl {TYPE_1__ timeout; } ;

/* Variables and functions */
 unsigned long HZ ; 

__attribute__((used)) static int autofs_dev_ioctl_timeout(struct file *fp,
				    struct autofs_sb_info *sbi,
				    struct autofs_dev_ioctl *param)
{
	unsigned long timeout;

	timeout = param->timeout.timeout;
	param->timeout.timeout = sbi->exp_timeout / HZ;
	sbi->exp_timeout = timeout * HZ;
	return 0;
}