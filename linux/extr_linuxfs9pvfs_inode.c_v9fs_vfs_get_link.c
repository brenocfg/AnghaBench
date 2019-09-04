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
struct v9fs_session_info {int dummy; } ;
struct p9_wstat {int mode; char* extension; } ;
struct p9_fid {int mode; char* extension; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  EINVAL ; 
 char const* ERR_CAST (struct p9_wstat*) ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct p9_wstat*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int P9_DMSYMLINK ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  kfree (struct p9_wstat*) ; 
 int /*<<< orphan*/  kfree_link ; 
 struct p9_wstat* p9_client_stat (struct p9_wstat*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct dentry*) ; 
 int /*<<< orphan*/  p9stat_free (struct p9_wstat*) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 struct v9fs_session_info* v9fs_dentry2v9ses (struct dentry*) ; 
 struct p9_wstat* v9fs_fid_lookup (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_proto_dotu (struct v9fs_session_info*) ; 

__attribute__((used)) static const char *v9fs_vfs_get_link(struct dentry *dentry,
				     struct inode *inode,
				     struct delayed_call *done)
{
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;
	struct p9_wstat *st;
	char *res;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	v9ses = v9fs_dentry2v9ses(dentry);
	fid = v9fs_fid_lookup(dentry);
	p9_debug(P9_DEBUG_VFS, "%pd\n", dentry);

	if (IS_ERR(fid))
		return ERR_CAST(fid);

	if (!v9fs_proto_dotu(v9ses))
		return ERR_PTR(-EBADF);

	st = p9_client_stat(fid);
	if (IS_ERR(st))
		return ERR_CAST(st);

	if (!(st->mode & P9_DMSYMLINK)) {
		p9stat_free(st);
		kfree(st);
		return ERR_PTR(-EINVAL);
	}
	res = st->extension;
	st->extension = NULL;
	if (strlen(res) >= PATH_MAX)
		res[PATH_MAX - 1] = '\0';

	p9stat_free(st);
	kfree(st);
	set_delayed_call(done, kfree_link, res);
	return res;
}