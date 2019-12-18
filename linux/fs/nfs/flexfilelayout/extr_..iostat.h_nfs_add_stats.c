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
struct inode {int dummy; } ;
typedef  enum nfs_stat_bytecounters { ____Placeholder_nfs_stat_bytecounters } nfs_stat_bytecounters ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (struct inode const*) ; 
 int /*<<< orphan*/  nfs_add_server_stats (int /*<<< orphan*/ ,int,long) ; 

__attribute__((used)) static inline void nfs_add_stats(const struct inode *inode,
				 enum nfs_stat_bytecounters stat,
				 long addend)
{
	nfs_add_server_stats(NFS_SERVER(inode), stat, addend);
}