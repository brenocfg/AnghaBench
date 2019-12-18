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
 int OCFS2_HAS_REFCOUNT_FL ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 

__attribute__((used)) static inline bool ocfs2_is_refcount_inode(struct inode *inode)
{
	return (OCFS2_I(inode)->ip_dyn_features & OCFS2_HAS_REFCOUNT_FL);
}