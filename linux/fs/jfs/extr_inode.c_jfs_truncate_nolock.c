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
typedef  int /*<<< orphan*/  tid_t ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int COMMIT_PWMAP ; 
 int COMMIT_TRUNCATE ; 
 int COMMIT_WMAP ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 scalar_t__ xtTruncate (int /*<<< orphan*/ ,struct inode*,scalar_t__,int) ; 

void jfs_truncate_nolock(struct inode *ip, loff_t length)
{
	loff_t newsize;
	tid_t tid;

	ASSERT(length >= 0);

	if (test_cflag(COMMIT_Nolink, ip)) {
		xtTruncate(0, ip, length, COMMIT_WMAP);
		return;
	}

	do {
		tid = txBegin(ip->i_sb, 0);

		/*
		 * The commit_mutex cannot be taken before txBegin.
		 * txBegin may block and there is a chance the inode
		 * could be marked dirty and need to be committed
		 * before txBegin unblocks
		 */
		mutex_lock(&JFS_IP(ip)->commit_mutex);

		newsize = xtTruncate(tid, ip, length,
				     COMMIT_TRUNCATE | COMMIT_PWMAP);
		if (newsize < 0) {
			txEnd(tid);
			mutex_unlock(&JFS_IP(ip)->commit_mutex);
			break;
		}

		ip->i_mtime = ip->i_ctime = current_time(ip);
		mark_inode_dirty(ip);

		txCommit(tid, 1, &ip, 0);
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
	} while (newsize > length);	/* Truncate isn't always atomic */
}