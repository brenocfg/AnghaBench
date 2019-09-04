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
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 unsigned int LOOKUP_EXCL ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 

__attribute__((used)) static int nfs_is_exclusive_create(struct inode *dir, unsigned int flags)
{
	if (NFS_PROTO(dir)->version == 2)
		return 0;
	return flags & LOOKUP_EXCL;
}