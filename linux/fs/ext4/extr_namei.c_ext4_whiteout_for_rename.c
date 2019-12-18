#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; } ;
struct ext4_renament {TYPE_2__* dir; TYPE_1__* dentry; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_DIR ; 
 scalar_t__ EXT4_MAXQUOTAS_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT4_XATTR_TRANS_BLOCKS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  WHITEOUT_DEV ; 
 int WHITEOUT_MODE ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 struct inode* ext4_new_inode_start_handle (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_special_inode_operations ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *ext4_whiteout_for_rename(struct ext4_renament *ent,
					      int credits, handle_t **h)
{
	struct inode *wh;
	handle_t *handle;
	int retries = 0;

	/*
	 * for inode block, sb block, group summaries,
	 * and inode bitmap
	 */
	credits += (EXT4_MAXQUOTAS_TRANS_BLOCKS(ent->dir->i_sb) +
		    EXT4_XATTR_TRANS_BLOCKS + 4);
retry:
	wh = ext4_new_inode_start_handle(ent->dir, S_IFCHR | WHITEOUT_MODE,
					 &ent->dentry->d_name, 0, NULL,
					 EXT4_HT_DIR, credits);

	handle = ext4_journal_current_handle();
	if (IS_ERR(wh)) {
		if (handle)
			ext4_journal_stop(handle);
		if (PTR_ERR(wh) == -ENOSPC &&
		    ext4_should_retry_alloc(ent->dir->i_sb, &retries))
			goto retry;
	} else {
		*h = handle;
		init_special_inode(wh, wh->i_mode, WHITEOUT_DEV);
		wh->i_op = &ext4_special_inode_operations;
	}
	return wh;
}