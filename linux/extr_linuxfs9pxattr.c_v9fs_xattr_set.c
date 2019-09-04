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

/* Variables and functions */
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 
 int v9fs_fid_xattr_set (struct p9_fid*,char const*,void const*,size_t,int) ; 

int v9fs_xattr_set(struct dentry *dentry, const char *name,
		   const void *value, size_t value_len, int flags)
{
	struct p9_fid *fid = v9fs_fid_lookup(dentry);
	return v9fs_fid_xattr_set(fid, name, value, value_len, flags);
}