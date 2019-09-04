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
struct jffs2_sb_info {int dummy; } ;
struct jffs2_raw_inode {int dummy; } ;
struct jffs2_inode_info {int /*<<< orphan*/  sem; struct jffs2_inode_cache* inocache; } ;
struct jffs2_inode_cache {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  jffs2_do_clear_inode (struct jffs2_sb_info*,struct jffs2_inode_info*) ; 
 int jffs2_do_read_inode_internal (struct jffs2_sb_info*,struct jffs2_inode_info*,struct jffs2_raw_inode*) ; 
 int /*<<< orphan*/  jffs2_xattr_do_crccheck_inode (struct jffs2_sb_info*,struct jffs2_inode_cache*) ; 
 int /*<<< orphan*/  kfree (struct jffs2_inode_info*) ; 
 struct jffs2_inode_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int jffs2_do_crccheck_inode(struct jffs2_sb_info *c, struct jffs2_inode_cache *ic)
{
	struct jffs2_raw_inode n;
	struct jffs2_inode_info *f = kzalloc(sizeof(*f), GFP_KERNEL);
	int ret;

	if (!f)
		return -ENOMEM;

	mutex_init(&f->sem);
	mutex_lock(&f->sem);
	f->inocache = ic;

	ret = jffs2_do_read_inode_internal(c, f, &n);
	mutex_unlock(&f->sem);
	jffs2_do_clear_inode(c, f);
	jffs2_xattr_do_crccheck_inode(c, ic);
	kfree (f);
	return ret;
}