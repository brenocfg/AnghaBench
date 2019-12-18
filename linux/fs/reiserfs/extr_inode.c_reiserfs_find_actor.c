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
struct reiserfs_iget_args {scalar_t__ objectid; scalar_t__ dirid; } ;
struct inode {scalar_t__ i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

int reiserfs_find_actor(struct inode *inode, void *opaque)
{
	struct reiserfs_iget_args *args;

	args = opaque;
	/* args is already in CPU order */
	return (inode->i_ino == args->objectid) &&
	    (le32_to_cpu(INODE_PKEY(inode)->k_dir_id) == args->dirid);
}