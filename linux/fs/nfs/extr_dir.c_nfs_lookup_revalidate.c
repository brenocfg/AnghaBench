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
struct dentry {int dummy; } ;

/* Variables and functions */
 int __nfs_lookup_revalidate (struct dentry*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_do_lookup_revalidate ; 

__attribute__((used)) static int nfs_lookup_revalidate(struct dentry *dentry, unsigned int flags)
{
	return __nfs_lookup_revalidate(dentry, flags, nfs_do_lookup_revalidate);
}