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

/* Variables and functions */
 scalar_t__ ovl_has_upperdata (struct inode*) ; 
 struct inode* ovl_inode_lowerdata (struct inode*) ; 
 struct inode* ovl_inode_upper (struct inode*) ; 

struct inode *ovl_inode_realdata(struct inode *inode)
{
	struct inode *upperinode;

	upperinode = ovl_inode_upper(inode);
	if (upperinode && ovl_has_upperdata(inode))
		return upperinode;

	return ovl_inode_lowerdata(inode);
}