#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; } ;
typedef  int /*<<< orphan*/  qsize_t ;
struct TYPE_4__ {TYPE_1__* dq_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_reserved_space; } ;

/* Variables and functions */
 int /*<<< orphan*/ * inode_reserved_space (struct inode*) ; 

__attribute__((used)) static qsize_t __inode_get_rsv_space(struct inode *inode)
{
	if (!inode->i_sb->dq_op->get_reserved_space)
		return 0;
	return *inode_reserved_space(inode);
}