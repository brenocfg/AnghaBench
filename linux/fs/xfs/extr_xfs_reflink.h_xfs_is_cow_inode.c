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
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ xfs_is_always_cow_inode (struct xfs_inode*) ; 
 scalar_t__ xfs_is_reflink_inode (struct xfs_inode*) ; 

__attribute__((used)) static inline bool xfs_is_cow_inode(struct xfs_inode *ip)
{
	return xfs_is_reflink_inode(ip) || xfs_is_always_cow_inode(ip);
}