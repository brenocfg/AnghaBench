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
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct gb_cap {int dummy; } ;
struct file {struct gb_cap* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 struct gb_cap* get_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cap_open(struct inode *inode, struct file *file)
{
	struct gb_cap *cap = get_cap(inode->i_cdev);

	/* cap structure can't get freed until file descriptor is closed */
	if (cap) {
		file->private_data = cap;
		return 0;
	}

	return -ENODEV;
}