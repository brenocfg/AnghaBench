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
typedef  union fuse_dentry {int dummy; } fuse_dentry ;
struct dentry {scalar_t__ d_fsdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL_ACCOUNT ; 
 int __GFP_RECLAIMABLE ; 
 scalar_t__ kzalloc (int,int) ; 

__attribute__((used)) static int fuse_dentry_init(struct dentry *dentry)
{
	dentry->d_fsdata = kzalloc(sizeof(union fuse_dentry),
				   GFP_KERNEL_ACCOUNT | __GFP_RECLAIMABLE);

	return dentry->d_fsdata ? 0 : -ENOMEM;
}