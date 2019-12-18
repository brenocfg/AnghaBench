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
struct nfs_commit_info {int dummy; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int PNFS_NOT_ATTEMPTED ; 

__attribute__((used)) static inline int
pnfs_commit_list(struct inode *inode, struct list_head *mds_pages, int how,
		 struct nfs_commit_info *cinfo)
{
	return PNFS_NOT_ATTEMPTED;
}