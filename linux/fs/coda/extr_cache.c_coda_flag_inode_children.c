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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_flag_children (struct dentry*,int) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 

void coda_flag_inode_children(struct inode *inode, int flag)
{
	struct dentry *alias_de;

	if ( !inode || !S_ISDIR(inode->i_mode)) 
		return; 

	alias_de = d_find_alias(inode);
	if (!alias_de)
		return;
	coda_flag_children(alias_de, flag);
	shrink_dcache_parent(alias_de);
	dput(alias_de);
}