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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {scalar_t__ lowerdata; } ;

/* Variables and functions */
 TYPE_1__* OVL_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct inode* ovl_inode_lower (struct inode*) ; 

struct inode *ovl_inode_lowerdata(struct inode *inode)
{
	if (WARN_ON(!S_ISREG(inode->i_mode)))
		return NULL;

	return OVL_I(inode)->lowerdata ?: ovl_inode_lower(inode);
}