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
struct super_block {scalar_t__ s_blocksize_bits; int /*<<< orphan*/  s_bdev; } ;
struct jfs_log {scalar_t__ l2bsize; int /*<<< orphan*/  sb_list; scalar_t__ size; int /*<<< orphan*/  base; int /*<<< orphan*/  bdev; int /*<<< orphan*/  flag; int /*<<< orphan*/  syncwait; } ;
struct TYPE_2__ {struct jfs_log* log; int /*<<< orphan*/  log_list; int /*<<< orphan*/  logpxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* JFS_SBI (struct super_block*) ; 
 scalar_t__ L2LOGPSIZE ; 
 int /*<<< orphan*/  addressPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_warn (char*,int) ; 
 int /*<<< orphan*/  kfree (struct jfs_log*) ; 
 struct jfs_log* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ lengthPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lmLogInit (struct jfs_log*) ; 
 int /*<<< orphan*/  log_INLINELOG ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int open_inline_log(struct super_block *sb)
{
	struct jfs_log *log;
	int rc;

	if (!(log = kzalloc(sizeof(struct jfs_log), GFP_KERNEL)))
		return -ENOMEM;
	INIT_LIST_HEAD(&log->sb_list);
	init_waitqueue_head(&log->syncwait);

	set_bit(log_INLINELOG, &log->flag);
	log->bdev = sb->s_bdev;
	log->base = addressPXD(&JFS_SBI(sb)->logpxd);
	log->size = lengthPXD(&JFS_SBI(sb)->logpxd) >>
	    (L2LOGPSIZE - sb->s_blocksize_bits);
	log->l2bsize = sb->s_blocksize_bits;
	ASSERT(L2LOGPSIZE >= sb->s_blocksize_bits);

	/*
	 * initialize log.
	 */
	if ((rc = lmLogInit(log))) {
		kfree(log);
		jfs_warn("lmLogOpen: exit(%d)", rc);
		return rc;
	}

	list_add(&JFS_SBI(sb)->log_list, &log->sb_list);
	JFS_SBI(sb)->log = log;

	return rc;
}