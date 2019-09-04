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
struct udf_fileident_bh {scalar_t__ sbh; scalar_t__ ebh; } ;
struct qstr {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  extLocation; } ;
struct fileIdentDesc {TYPE_1__ icb; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct qstr QSTR_INIT (char*,int) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct kernel_lb_addr lelb_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_find_entry (int /*<<< orphan*/ ,struct qstr*,struct udf_fileident_bh*,struct fileIdentDesc*) ; 
 struct inode* udf_iget (int /*<<< orphan*/ ,struct kernel_lb_addr*) ; 

__attribute__((used)) static struct dentry *udf_get_parent(struct dentry *child)
{
	struct kernel_lb_addr tloc;
	struct inode *inode = NULL;
	struct qstr dotdot = QSTR_INIT("..", 2);
	struct fileIdentDesc cfi;
	struct udf_fileident_bh fibh;

	if (!udf_find_entry(d_inode(child), &dotdot, &fibh, &cfi))
		return ERR_PTR(-EACCES);

	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);

	tloc = lelb_to_cpu(cfi.icb.extLocation);
	inode = udf_iget(child->d_sb, &tloc);
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	return d_obtain_alias(inode);
}