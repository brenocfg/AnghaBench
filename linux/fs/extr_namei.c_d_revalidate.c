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
struct dentry {int d_flags; TYPE_1__* d_op; } ;
struct TYPE_2__ {int (* d_revalidate ) (struct dentry*,unsigned int) ;} ;

/* Variables and functions */
 int DCACHE_OP_REVALIDATE ; 
 int stub1 (struct dentry*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int d_revalidate(struct dentry *dentry, unsigned int flags)
{
	if (unlikely(dentry->d_flags & DCACHE_OP_REVALIDATE))
		return dentry->d_op->d_revalidate(dentry, flags);
	else
		return 1;
}