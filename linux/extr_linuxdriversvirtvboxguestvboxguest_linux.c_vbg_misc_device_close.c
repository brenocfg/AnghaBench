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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vbg_core_close_session (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vbg_misc_device_close(struct inode *inode, struct file *filp)
{
	vbg_core_close_session(filp->private_data);
	filp->private_data = NULL;
	return 0;
}