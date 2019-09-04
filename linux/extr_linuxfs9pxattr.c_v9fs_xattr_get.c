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
struct p9_fid {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_fid_xattr_get (struct p9_fid*,char const*,void*,size_t) ; 

ssize_t v9fs_xattr_get(struct dentry *dentry, const char *name,
		       void *buffer, size_t buffer_size)
{
	struct p9_fid *fid;

	p9_debug(P9_DEBUG_VFS, "name = %s value_len = %zu\n",
		 name, buffer_size);
	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid))
		return PTR_ERR(fid);

	return v9fs_fid_xattr_get(fid, name, buffer, buffer_size);
}