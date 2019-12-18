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
struct super_block {int s_flags; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_op; TYPE_1__* s_mtd; struct jffs2_sb_info* s_fs_info; } ;
struct jffs2_sb_info {int /*<<< orphan*/  inocache_lock; int /*<<< orphan*/  erase_completion_lock; int /*<<< orphan*/  inocache_wq; int /*<<< orphan*/  erase_wait; int /*<<< orphan*/  erase_free_sem; int /*<<< orphan*/  alloc_sem; struct super_block* os_priv; TYPE_1__* mtd; } ;
struct fs_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int SB_NOATIME ; 
 int SB_POSIXACL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jffs2_do_fill_super (struct super_block*,struct fs_context*) ; 
 int /*<<< orphan*/  jffs2_export_ops ; 
 int /*<<< orphan*/  jffs2_super_operations ; 
 int /*<<< orphan*/  jffs2_xattr_handlers ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jffs2_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct jffs2_sb_info *c = sb->s_fs_info;

	jffs2_dbg(1, "jffs2_get_sb_mtd():"
		  " New superblock for device %d (\"%s\")\n",
		  sb->s_mtd->index, sb->s_mtd->name);

	c->mtd = sb->s_mtd;
	c->os_priv = sb;

	/* Initialize JFFS2 superblock locks, the further initialization will
	 * be done later */
	mutex_init(&c->alloc_sem);
	mutex_init(&c->erase_free_sem);
	init_waitqueue_head(&c->erase_wait);
	init_waitqueue_head(&c->inocache_wq);
	spin_lock_init(&c->erase_completion_lock);
	spin_lock_init(&c->inocache_lock);

	sb->s_op = &jffs2_super_operations;
	sb->s_export_op = &jffs2_export_ops;
	sb->s_flags = sb->s_flags | SB_NOATIME;
	sb->s_xattr = jffs2_xattr_handlers;
#ifdef CONFIG_JFFS2_FS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#endif
	return jffs2_do_fill_super(sb, fc);
}