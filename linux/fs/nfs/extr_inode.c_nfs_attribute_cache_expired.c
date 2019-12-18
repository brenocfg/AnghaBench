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

/* Variables and functions */
 int nfs_attribute_timeout (struct inode*) ; 
 scalar_t__ nfs_have_delegated_attributes (struct inode*) ; 

int nfs_attribute_cache_expired(struct inode *inode)
{
	if (nfs_have_delegated_attributes(inode))
		return 0;
	return nfs_attribute_timeout(inode);
}