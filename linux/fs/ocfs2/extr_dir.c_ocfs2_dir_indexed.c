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
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INDEXED_DIR_FL ; 

__attribute__((used)) static int ocfs2_dir_indexed(struct inode *inode)
{
	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INDEXED_DIR_FL)
		return 1;
	return 0;
}