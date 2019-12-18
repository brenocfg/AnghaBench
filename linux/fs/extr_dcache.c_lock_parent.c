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
struct dentry {int /*<<< orphan*/  d_lock; struct dentry* d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ROOT (struct dentry*) ; 
 struct dentry* __lock_parent (struct dentry*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct dentry *lock_parent(struct dentry *dentry)
{
	struct dentry *parent = dentry->d_parent;
	if (IS_ROOT(dentry))
		return NULL;
	if (likely(spin_trylock(&parent->d_lock)))
		return parent;
	return __lock_parent(dentry);
}