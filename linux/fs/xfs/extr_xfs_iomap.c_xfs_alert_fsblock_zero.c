#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ i_ino; int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct TYPE_6__ {int /*<<< orphan*/  br_state; scalar_t__ br_blockcount; scalar_t__ br_startoff; scalar_t__ br_startblock; } ;
typedef  TYPE_2__ xfs_bmbt_irec_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_PTAG_FSBLOCK_ZERO ; 
 int /*<<< orphan*/  xfs_alert_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_alert_fsblock_zero(
	xfs_inode_t	*ip,
	xfs_bmbt_irec_t	*imap)
{
	xfs_alert_tag(ip->i_mount, XFS_PTAG_FSBLOCK_ZERO,
			"Access to block zero in inode %llu "
			"start_block: %llx start_off: %llx "
			"blkcnt: %llx extent-state: %x",
		(unsigned long long)ip->i_ino,
		(unsigned long long)imap->br_startblock,
		(unsigned long long)imap->br_startoff,
		(unsigned long long)imap->br_blockcount,
		imap->br_state);
	return -EFSCORRUPTED;
}