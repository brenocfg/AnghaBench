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
struct inode {int dummy; } ;
struct TYPE_2__ {int cache_validity; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ATTR ; 
 int NFS_INO_INVALID_LABEL ; 
 scalar_t__ nfs_attribute_cache_expired (struct inode*) ; 

__attribute__((used)) static bool nfs_need_revalidate_inode(struct inode *inode)
{
	if (NFS_I(inode)->cache_validity &
			(NFS_INO_INVALID_ATTR|NFS_INO_INVALID_LABEL))
		return true;
	if (nfs_attribute_cache_expired(inode))
		return true;
	return false;
}