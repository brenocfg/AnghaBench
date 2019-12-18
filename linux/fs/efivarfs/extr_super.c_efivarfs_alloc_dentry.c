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
struct qstr {char* name; int /*<<< orphan*/  len; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 int efivarfs_d_hash (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static struct dentry *efivarfs_alloc_dentry(struct dentry *parent, char *name)
{
	struct dentry *d;
	struct qstr q;
	int err;

	q.name = name;
	q.len = strlen(name);

	err = efivarfs_d_hash(parent, &q);
	if (err)
		return ERR_PTR(err);

	d = d_alloc(parent, &q);
	if (d)
		return d;

	return ERR_PTR(-ENOMEM);
}