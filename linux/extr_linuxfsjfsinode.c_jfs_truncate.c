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
typedef  int /*<<< orphan*/  ulong ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWRITE_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWRITE_UNLOCK (struct inode*) ; 
 int /*<<< orphan*/  RDWRLOCK_NORMAL ; 
 int /*<<< orphan*/  jfs_get_block ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_truncate_nolock (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  nobh_truncate_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void jfs_truncate(struct inode *ip)
{
	jfs_info("jfs_truncate: size = 0x%lx", (ulong) ip->i_size);

	nobh_truncate_page(ip->i_mapping, ip->i_size, jfs_get_block);

	IWRITE_LOCK(ip, RDWRLOCK_NORMAL);
	jfs_truncate_nolock(ip, ip->i_size);
	IWRITE_UNLOCK(ip);
}