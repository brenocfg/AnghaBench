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
struct super_block {int dummy; } ;
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_NORCU ; 
 struct dentry* __d_alloc (struct super_block*,struct qstr const*) ; 
 scalar_t__ likely (struct dentry*) ; 

struct dentry *d_alloc_pseudo(struct super_block *sb, const struct qstr *name)
{
	struct dentry *dentry = __d_alloc(sb, name);
	if (likely(dentry))
		dentry->d_flags |= DCACHE_NORCU;
	return dentry;
}