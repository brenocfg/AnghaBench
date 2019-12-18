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
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_nlink; } ;

/* Variables and functions */
 TYPE_1__* d_backing_inode (struct dentry*) ; 
 scalar_t__ d_unlinked (struct dentry*) ; 

__attribute__((used)) static inline bool is_deleted(struct dentry *dentry)
{
	if (d_unlinked(dentry) && d_backing_inode(dentry)->i_nlink == 0)
		return 1;
	return 0;
}