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
struct orangefs_dir_part {struct orangefs_dir_part* next; } ;
struct orangefs_dir {struct orangefs_dir_part* part; } ;
struct inode {int dummy; } ;
struct file {struct orangefs_dir* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct orangefs_dir*) ; 
 int /*<<< orphan*/  vfree (struct orangefs_dir_part*) ; 

__attribute__((used)) static int orangefs_dir_release(struct inode *inode, struct file *file)
{
	struct orangefs_dir *od = file->private_data;
	struct orangefs_dir_part *part = od->part;
	while (part) {
		struct orangefs_dir_part *next = part->next;
		vfree(part);
		part = next;
	}
	kfree(od);
	return 0;
}