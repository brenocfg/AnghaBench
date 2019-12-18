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
struct seq_file {int /*<<< orphan*/  private; } ;
struct TYPE_2__ {int /*<<< orphan*/  prop; } ;
struct op_inode_info {scalar_t__ type; TYPE_1__ u; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct op_inode_info* OP_I (struct inode*) ; 
 scalar_t__ op_inode_prop ; 
 int /*<<< orphan*/  property_op ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int property_open(struct inode *inode, struct file *file)
{
	struct op_inode_info *oi = OP_I(inode);
	int ret;

	BUG_ON(oi->type != op_inode_prop);

	ret = seq_open(file, &property_op);
	if (!ret) {
		struct seq_file *m = file->private_data;
		m->private = oi->u.prop;
	}
	return ret;
}