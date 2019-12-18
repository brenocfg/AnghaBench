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
struct orangefs_dir {int end; scalar_t__ error; int /*<<< orphan*/ * part; int /*<<< orphan*/  token; } ;
struct inode {int dummy; } ;
struct file {struct orangefs_dir* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ORANGEFS_ITERATE_START ; 
 int PART_SHIFT ; 
 struct orangefs_dir* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orangefs_dir_open(struct inode *inode, struct file *file)
{
	struct orangefs_dir *od;
	file->private_data = kmalloc(sizeof(struct orangefs_dir),
	    GFP_KERNEL);
	if (!file->private_data)
		return -ENOMEM;
	od = file->private_data;
	od->token = ORANGEFS_ITERATE_START;
	od->part = NULL;
	od->end = 1 << PART_SHIFT;
	od->error = 0;
	return 0;
}