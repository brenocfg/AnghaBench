#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tv_sec; } ;
struct TYPE_8__ {int tv_sec; } ;
struct TYPE_7__ {int tv_sec; } ;
struct inode {TYPE_1__ i_mtime; TYPE_3__ i_atime; TYPE_2__ i_ctime; } ;
struct dentry {int dummy; } ;
struct TYPE_10__ {int tz_secondswest; } ;
struct TYPE_9__ {int tz_minuteswest; } ;

/* Variables and functions */
 int ECHILD ; 
 TYPE_5__* HFS_I (struct inode*) ; 
 unsigned int LOOKUP_RCU ; 
 struct inode* d_inode (struct dentry*) ; 
 TYPE_4__ sys_tz ; 

__attribute__((used)) static int hfs_revalidate_dentry(struct dentry *dentry, unsigned int flags)
{
	struct inode *inode;
	int diff;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	inode = d_inode(dentry);
	if(!inode)
		return 1;

	/* fix up inode on a timezone change */
	diff = sys_tz.tz_minuteswest * 60 - HFS_I(inode)->tz_secondswest;
	if (diff) {
		inode->i_ctime.tv_sec += diff;
		inode->i_atime.tv_sec += diff;
		inode->i_mtime.tv_sec += diff;
		HFS_I(inode)->tz_secondswest += diff;
	}
	return 1;
}