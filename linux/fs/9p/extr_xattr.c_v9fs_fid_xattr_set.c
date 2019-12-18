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
struct kvec {void* iov_base; size_t iov_len; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  WRITE ; 
 struct p9_fid* clone_fid (struct p9_fid*) ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 int p9_client_clunk (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_write (struct p9_fid*,int /*<<< orphan*/ ,struct iov_iter*,int*) ; 
 int p9_client_xattrcreate (struct p9_fid*,char const*,size_t,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 

int v9fs_fid_xattr_set(struct p9_fid *fid, const char *name,
		   const void *value, size_t value_len, int flags)
{
	struct kvec kvec = {.iov_base = (void *)value, .iov_len = value_len};
	struct iov_iter from;
	int retval, err;

	iov_iter_kvec(&from, WRITE, &kvec, 1, value_len);

	p9_debug(P9_DEBUG_VFS, "name = %s value_len = %zu flags = %d\n",
		 name, value_len, flags);

	/* Clone it */
	fid = clone_fid(fid);
	if (IS_ERR(fid))
		return PTR_ERR(fid);

	/*
	 * On success fid points to xattr
	 */
	retval = p9_client_xattrcreate(fid, name, value_len, flags);
	if (retval < 0)
		p9_debug(P9_DEBUG_VFS, "p9_client_xattrcreate failed %d\n",
			 retval);
	else
		p9_client_write(fid, 0, &from, &retval);
	err = p9_client_clunk(fid);
	if (!retval && err)
		retval = err;
	return retval;
}