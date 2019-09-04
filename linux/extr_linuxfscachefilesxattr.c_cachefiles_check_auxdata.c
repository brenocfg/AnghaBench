#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct cachefiles_xattr {scalar_t__ type; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__* cookie; } ;
struct cachefiles_object {TYPE_3__ fscache; struct dentry* dentry; } ;
typedef  int ssize_t ;
typedef  enum fscache_checkaux { ____Placeholder_fscache_checkaux } fscache_checkaux ;
struct TYPE_5__ {TYPE_1__* def; } ;
struct TYPE_4__ {scalar_t__ type; struct dentry* check_aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct dentry*) ; 
 int ENOMEM ; 
 int ESTALE ; 
 int FSCACHE_CHECKAUX_OKAY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cachefiles_xattr_cache ; 
 struct dentry* d_backing_inode (struct dentry*) ; 
 int fscache_check_aux (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct dentry*) ; 
 int /*<<< orphan*/  kfree (struct cachefiles_xattr*) ; 
 struct cachefiles_xattr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int vfs_getxattr (struct dentry*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

int cachefiles_check_auxdata(struct cachefiles_object *object)
{
	struct cachefiles_xattr *auxbuf;
	enum fscache_checkaux validity;
	struct dentry *dentry = object->dentry;
	ssize_t xlen;
	int ret;

	ASSERT(dentry);
	ASSERT(d_backing_inode(dentry));
	ASSERT(object->fscache.cookie->def->check_aux);

	auxbuf = kmalloc(sizeof(struct cachefiles_xattr) + 512, GFP_KERNEL);
	if (!auxbuf)
		return -ENOMEM;

	xlen = vfs_getxattr(dentry, cachefiles_xattr_cache,
			    &auxbuf->type, 512 + 1);
	ret = -ESTALE;
	if (xlen < 1 ||
	    auxbuf->type != object->fscache.cookie->def->type)
		goto error;

	xlen--;
	validity = fscache_check_aux(&object->fscache, &auxbuf->data, xlen,
				     i_size_read(d_backing_inode(dentry)));
	if (validity != FSCACHE_CHECKAUX_OKAY)
		goto error;

	ret = 0;
error:
	kfree(auxbuf);
	return ret;
}