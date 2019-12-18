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
typedef  size_t u64 ;
struct p9_fid {int dummy; } ;
struct kvec {void* iov_base; size_t iov_len; } ;
struct iov_iter {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,size_t) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_read (struct p9_fid*,int /*<<< orphan*/ ,struct iov_iter*,int*) ; 
 struct p9_fid* p9_client_xattrwalk (struct p9_fid*,char const*,size_t*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int) ; 

ssize_t v9fs_fid_xattr_get(struct p9_fid *fid, const char *name,
			   void *buffer, size_t buffer_size)
{
	ssize_t retval;
	u64 attr_size;
	struct p9_fid *attr_fid;
	struct kvec kvec = {.iov_base = buffer, .iov_len = buffer_size};
	struct iov_iter to;
	int err;

	iov_iter_kvec(&to, READ, &kvec, 1, buffer_size);

	attr_fid = p9_client_xattrwalk(fid, name, &attr_size);
	if (IS_ERR(attr_fid)) {
		retval = PTR_ERR(attr_fid);
		p9_debug(P9_DEBUG_VFS, "p9_client_attrwalk failed %zd\n",
			 retval);
		return retval;
	}
	if (attr_size > buffer_size) {
		if (!buffer_size) /* request to get the attr_size */
			retval = attr_size;
		else
			retval = -ERANGE;
	} else {
		iov_iter_truncate(&to, attr_size);
		retval = p9_client_read(attr_fid, 0, &to, &err);
		if (err)
			retval = err;
	}
	p9_client_clunk(attr_fid);
	return retval;
}