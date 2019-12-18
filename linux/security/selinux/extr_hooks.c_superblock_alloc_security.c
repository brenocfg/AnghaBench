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
struct superblock_security_struct {void* mntpoint_sid; int /*<<< orphan*/  def_sid; void* sid; struct super_block* sb; int /*<<< orphan*/  isec_lock; int /*<<< orphan*/  isec_head; int /*<<< orphan*/  lock; } ;
struct super_block {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECINITSID_FILE ; 
 void* SECINITSID_UNLABELED ; 
 struct superblock_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int superblock_alloc_security(struct super_block *sb)
{
	struct superblock_security_struct *sbsec;

	sbsec = kzalloc(sizeof(struct superblock_security_struct), GFP_KERNEL);
	if (!sbsec)
		return -ENOMEM;

	mutex_init(&sbsec->lock);
	INIT_LIST_HEAD(&sbsec->isec_head);
	spin_lock_init(&sbsec->isec_lock);
	sbsec->sb = sb;
	sbsec->sid = SECINITSID_UNLABELED;
	sbsec->def_sid = SECINITSID_FILE;
	sbsec->mntpoint_sid = SECINITSID_UNLABELED;
	sb->s_security = sbsec;

	return 0;
}