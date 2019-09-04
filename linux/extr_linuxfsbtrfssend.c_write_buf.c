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
typedef  scalar_t__ u32 ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 int kernel_write (struct file*,void const*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_buf(struct file *filp, const void *buf, u32 len, loff_t *off)
{
	int ret;
	u32 pos = 0;

	while (pos < len) {
		ret = kernel_write(filp, buf + pos, len - pos, off);
		/* TODO handle that correctly */
		/*if (ret == -ERESTARTSYS) {
			continue;
		}*/
		if (ret < 0)
			return ret;
		if (ret == 0) {
			return -EIO;
		}
		pos += ret;
	}

	return 0;
}