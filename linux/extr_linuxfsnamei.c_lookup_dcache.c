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
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr const*) ; 
 int d_revalidate (struct dentry*,unsigned int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dentry *lookup_dcache(const struct qstr *name,
				    struct dentry *dir,
				    unsigned int flags)
{
	struct dentry *dentry = d_lookup(dir, name);
	if (dentry) {
		int error = d_revalidate(dentry, flags);
		if (unlikely(error <= 0)) {
			if (!error)
				d_invalidate(dentry);
			dput(dentry);
			return ERR_PTR(error);
		}
	}
	return dentry;
}