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
struct TYPE_2__ {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 TYPE_1__* PDE (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 

__attribute__((used)) static int proc_misc_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	if (flags & LOOKUP_RCU)
		return -ECHILD;

	if (atomic_read(&PDE(d_inode(dentry))->in_use) < 0)
		return 0; /* revalidate */
	return 1;
}