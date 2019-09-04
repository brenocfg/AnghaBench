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
struct xfs_inode {TYPE_1__* i_cowfp; } ;
struct TYPE_2__ {scalar_t__ if_bytes; } ;

/* Variables and functions */

__attribute__((used)) static inline bool xfs_inode_has_cow_data(struct xfs_inode *ip)
{
	return ip->i_cowfp && ip->i_cowfp->if_bytes;
}