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
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int __orangefs_setattr (int /*<<< orphan*/ ,struct iattr*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  sync_inode_metadata (int /*<<< orphan*/ ,int) ; 

int orangefs_setattr(struct dentry *dentry, struct iattr *iattr)
{
	int ret;
	gossip_debug(GOSSIP_INODE_DEBUG, "__orangefs_setattr: called on %pd\n",
	    dentry);
	ret = setattr_prepare(dentry, iattr);
	if (ret)
	        goto out;
	ret = __orangefs_setattr(d_inode(dentry), iattr);
	sync_inode_metadata(d_inode(dentry), 1);
out:
	gossip_debug(GOSSIP_INODE_DEBUG, "orangefs_setattr: returning %d\n",
	    ret);
	return ret;
}