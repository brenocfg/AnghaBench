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
struct inode {int /*<<< orphan*/ * i_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_common_inode_operations ; 

void fuse_init_common(struct inode *inode)
{
	inode->i_op = &fuse_common_inode_operations;
}