#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct dentry {int d_flags; TYPE_2__ d_lockref; TYPE_1__* d_op; } ;
struct TYPE_3__ {scalar_t__ (* d_delete ) (struct dentry*) ;} ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int DCACHE_LRU_LIST ; 
 int DCACHE_OP_DELETE ; 
 int DCACHE_REFERENCED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 int /*<<< orphan*/  d_lru_add (struct dentry*) ; 
 int d_unhashed (struct dentry*) ; 
 scalar_t__ stub1 (struct dentry*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool retain_dentry(struct dentry *dentry)
{
	WARN_ON(d_in_lookup(dentry));

	/* Unreachable? Get rid of it */
	if (unlikely(d_unhashed(dentry)))
		return false;

	if (unlikely(dentry->d_flags & DCACHE_DISCONNECTED))
		return false;

	if (unlikely(dentry->d_flags & DCACHE_OP_DELETE)) {
		if (dentry->d_op->d_delete(dentry))
			return false;
	}
	/* retain; LRU fodder */
	dentry->d_lockref.count--;
	if (unlikely(!(dentry->d_flags & DCACHE_LRU_LIST)))
		d_lru_add(dentry);
	else if (unlikely(!(dentry->d_flags & DCACHE_REFERENCED)))
		dentry->d_flags |= DCACHE_REFERENCED;
	return true;
}