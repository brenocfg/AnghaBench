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
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct qstr QSTR_INIT (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 struct dentry* d_hash_and_lookup (struct dentry*,struct qstr*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct dentry *__rpc_lookup_create_exclusive(struct dentry *parent,
					  const char *name)
{
	struct qstr q = QSTR_INIT(name, strlen(name));
	struct dentry *dentry = d_hash_and_lookup(parent, &q);
	if (!dentry) {
		dentry = d_alloc(parent, &q);
		if (!dentry)
			return ERR_PTR(-ENOMEM);
	}
	if (d_really_is_negative(dentry))
		return dentry;
	dput(dentry);
	return ERR_PTR(-EEXIST);
}