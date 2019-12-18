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
struct dentry {int d_flags; int /*<<< orphan*/ * d_inode; } ;

/* Variables and functions */
 unsigned int DCACHE_ENTRY_TYPE ; 
 unsigned int DCACHE_FALLTHRU ; 
 int DCACHE_LRU_LIST ; 
 unsigned int READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,unsigned int) ; 
 int /*<<< orphan*/  nr_dentry_negative ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __d_clear_type_and_inode(struct dentry *dentry)
{
	unsigned flags = READ_ONCE(dentry->d_flags);

	flags &= ~(DCACHE_ENTRY_TYPE | DCACHE_FALLTHRU);
	WRITE_ONCE(dentry->d_flags, flags);
	dentry->d_inode = NULL;
	if (dentry->d_flags & DCACHE_LRU_LIST)
		this_cpu_inc(nr_dentry_negative);
}