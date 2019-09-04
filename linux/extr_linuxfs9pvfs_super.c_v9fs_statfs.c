#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v9fs_session_info {int dummy; } ;
struct p9_rstatfs {int fsid; int /*<<< orphan*/  namelen; int /*<<< orphan*/  ffree; int /*<<< orphan*/  files; int /*<<< orphan*/  bavail; int /*<<< orphan*/  bfree; int /*<<< orphan*/  blocks; int /*<<< orphan*/  bsize; int /*<<< orphan*/  type; } ;
struct p9_fid {int dummy; } ;
struct TYPE_2__ {int* val; } ;
struct kstatfs {int /*<<< orphan*/  f_namelen; TYPE_1__ f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int PTR_ERR (struct p9_fid*) ; 
 int p9_client_statfs (struct p9_fid*,struct p9_rstatfs*) ; 
 int simple_statfs (struct dentry*,struct kstatfs*) ; 
 struct v9fs_session_info* v9fs_dentry2v9ses (struct dentry*) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 

__attribute__((used)) static int v9fs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;
	struct p9_rstatfs rs;
	int res;

	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid)) {
		res = PTR_ERR(fid);
		goto done;
	}

	v9ses = v9fs_dentry2v9ses(dentry);
	if (v9fs_proto_dotl(v9ses)) {
		res = p9_client_statfs(fid, &rs);
		if (res == 0) {
			buf->f_type = rs.type;
			buf->f_bsize = rs.bsize;
			buf->f_blocks = rs.blocks;
			buf->f_bfree = rs.bfree;
			buf->f_bavail = rs.bavail;
			buf->f_files = rs.files;
			buf->f_ffree = rs.ffree;
			buf->f_fsid.val[0] = rs.fsid & 0xFFFFFFFFUL;
			buf->f_fsid.val[1] = (rs.fsid >> 32) & 0xFFFFFFFFUL;
			buf->f_namelen = rs.namelen;
		}
		if (res != -ENOSYS)
			goto done;
	}
	res = simple_statfs(dentry, buf);
done:
	return res;
}