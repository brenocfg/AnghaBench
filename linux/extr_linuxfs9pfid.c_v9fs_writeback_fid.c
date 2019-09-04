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
 struct p9_fid* ERR_PTR (int) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  O_RDWR ; 
 struct p9_fid* clone_fid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_open (struct p9_fid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_fid_lookup_with_uid (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct p9_fid *v9fs_writeback_fid(struct dentry *dentry)
{
	int err;
	struct p9_fid *fid;

	fid = clone_fid(v9fs_fid_lookup_with_uid(dentry, GLOBAL_ROOT_UID, 0));
	if (IS_ERR(fid))
		goto error_out;
	/*
	 * writeback fid will only be used to write back the
	 * dirty pages. We always request for the open fid in read-write
	 * mode so that a partial page write which result in page
	 * read can work.
	 */
	err = p9_client_open(fid, O_RDWR);
	if (err < 0) {
		p9_client_clunk(fid);
		fid = ERR_PTR(err);
		goto error_out;
	}
error_out:
	return fid;
}