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
struct scan_control {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int flags; scalar_t__ backing_dev_info; } ;

/* Variables and functions */
 int PF_SWAPWRITE ; 
 TYPE_1__* current ; 
 scalar_t__ inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  inode_write_congested (struct inode*) ; 

__attribute__((used)) static int may_write_to_inode(struct inode *inode, struct scan_control *sc)
{
	if (current->flags & PF_SWAPWRITE)
		return 1;
	if (!inode_write_congested(inode))
		return 1;
	if (inode_to_bdi(inode) == current->backing_dev_info)
		return 1;
	return 0;
}