#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v9fs_session_info {int flags; unsigned char* uname; int /*<<< orphan*/  rename_sem; int /*<<< orphan*/  aname; int /*<<< orphan*/  clnt; } ;
struct p9_fid {int dummy; } ;
struct TYPE_3__ {unsigned char const* name; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_2__* d_sb; TYPE_1__ d_name; struct dentry* d_parent; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_4__ {struct dentry* s_root; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 struct p9_fid* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_MAXWELEM ; 
 int V9FS_ACCESS_MASK ; 
 int V9FS_ACCESS_SINGLE ; 
 int /*<<< orphan*/  __add_fid (struct dentry*,struct p9_fid*) ; 
 int build_path_from_dentry (struct v9fs_session_info*,struct dentry*,unsigned char const***) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (unsigned char const**) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 struct p9_fid* p9_client_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,unsigned char const**,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct v9fs_session_info* v9fs_dentry2v9ses (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 struct p9_fid* v9fs_fid_find (struct dentry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 
 scalar_t__ v9fs_proto_dotu (struct v9fs_session_info*) ; 

__attribute__((used)) static struct p9_fid *v9fs_fid_lookup_with_uid(struct dentry *dentry,
					       kuid_t uid, int any)
{
	struct dentry *ds;
	const unsigned char **wnames, *uname;
	int i, n, l, clone, access;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid, *old_fid = NULL;

	v9ses = v9fs_dentry2v9ses(dentry);
	access = v9ses->flags & V9FS_ACCESS_MASK;
	fid = v9fs_fid_find(dentry, uid, any);
	if (fid)
		return fid;
	/*
	 * we don't have a matching fid. To do a TWALK we need
	 * parent fid. We need to prevent rename when we want to
	 * look at the parent.
	 */
	down_read(&v9ses->rename_sem);
	ds = dentry->d_parent;
	fid = v9fs_fid_find(ds, uid, any);
	if (fid) {
		/* Found the parent fid do a lookup with that */
		fid = p9_client_walk(fid, 1, &dentry->d_name.name, 1);
		goto fid_out;
	}
	up_read(&v9ses->rename_sem);

	/* start from the root and try to do a lookup */
	fid = v9fs_fid_find(dentry->d_sb->s_root, uid, any);
	if (!fid) {
		/* the user is not attached to the fs yet */
		if (access == V9FS_ACCESS_SINGLE)
			return ERR_PTR(-EPERM);

		if (v9fs_proto_dotu(v9ses) || v9fs_proto_dotl(v9ses))
				uname = NULL;
		else
			uname = v9ses->uname;

		fid = p9_client_attach(v9ses->clnt, NULL, uname, uid,
				       v9ses->aname);
		if (IS_ERR(fid))
			return fid;

		v9fs_fid_add(dentry->d_sb->s_root, fid);
	}
	/* If we are root ourself just return that */
	if (dentry->d_sb->s_root == dentry)
		return fid;
	/*
	 * Do a multipath walk with attached root.
	 * When walking parent we need to make sure we
	 * don't have a parallel rename happening
	 */
	down_read(&v9ses->rename_sem);
	n  = build_path_from_dentry(v9ses, dentry, &wnames);
	if (n < 0) {
		fid = ERR_PTR(n);
		goto err_out;
	}
	clone = 1;
	i = 0;
	while (i < n) {
		l = min(n - i, P9_MAXWELEM);
		/*
		 * We need to hold rename lock when doing a multipath
		 * walk to ensure none of the patch component change
		 */
		fid = p9_client_walk(fid, l, &wnames[i], clone);
		if (IS_ERR(fid)) {
			if (old_fid) {
				/*
				 * If we fail, clunk fid which are mapping
				 * to path component and not the last component
				 * of the path.
				 */
				p9_client_clunk(old_fid);
			}
			kfree(wnames);
			goto err_out;
		}
		old_fid = fid;
		i += l;
		clone = 0;
	}
	kfree(wnames);
fid_out:
	if (!IS_ERR(fid)) {
		spin_lock(&dentry->d_lock);
		if (d_unhashed(dentry)) {
			spin_unlock(&dentry->d_lock);
			p9_client_clunk(fid);
			fid = ERR_PTR(-ENOENT);
		} else {
			__add_fid(dentry, fid);
			spin_unlock(&dentry->d_lock);
		}
	}
err_out:
	up_read(&v9ses->rename_sem);
	return fid;
}