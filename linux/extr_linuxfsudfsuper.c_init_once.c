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
struct TYPE_2__ {int /*<<< orphan*/ * i_data; } ;
struct udf_inode_info {int /*<<< orphan*/  vfs_inode; TYPE_1__ i_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct udf_inode_info *ei = (struct udf_inode_info *)foo;

	ei->i_ext.i_data = NULL;
	inode_init_once(&ei->vfs_inode);
}