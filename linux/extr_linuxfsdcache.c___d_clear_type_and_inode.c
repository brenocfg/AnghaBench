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
struct dentry {int /*<<< orphan*/ * d_inode; int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 unsigned int DCACHE_ENTRY_TYPE ; 
 unsigned int DCACHE_FALLTHRU ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void __d_clear_type_and_inode(struct dentry *dentry)
{
	unsigned flags = READ_ONCE(dentry->d_flags);

	flags &= ~(DCACHE_ENTRY_TYPE | DCACHE_FALLTHRU);
	WRITE_ONCE(dentry->d_flags, flags);
	dentry->d_inode = NULL;
}