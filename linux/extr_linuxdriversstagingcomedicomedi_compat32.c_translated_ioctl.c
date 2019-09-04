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
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {int (* unlocked_ioctl ) (struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int ENOTTY ; 
 int stub1 (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static int translated_ioctl(struct file *file, unsigned int cmd,
			    unsigned long arg)
{
	if (file->f_op->unlocked_ioctl)
		return file->f_op->unlocked_ioctl(file, cmd, arg);

	return -ENOTTY;
}