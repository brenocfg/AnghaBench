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
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct dentry* __lookup_slow (struct qstr*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_is_locked (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_dcache (struct qstr*,struct dentry*,int /*<<< orphan*/ ) ; 
 int lookup_one_len_common (char const*,struct dentry*,int,struct qstr*) ; 

struct dentry *lookup_one_len(const char *name, struct dentry *base, int len)
{
	struct dentry *dentry;
	struct qstr this;
	int err;

	WARN_ON_ONCE(!inode_is_locked(base->d_inode));

	err = lookup_one_len_common(name, base, len, &this);
	if (err)
		return ERR_PTR(err);

	dentry = lookup_dcache(&this, base, 0);
	return dentry ? dentry : __lookup_slow(&this, base, 0);
}