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
typedef  int /*<<< orphan*/  u32 ;
struct v9fs_session_info {scalar_t__ cache; } ;
struct path {struct dentry* dentry; } ;
struct p9_stat_dotl {int /*<<< orphan*/  st_blksize; } ;
struct p9_fid {int /*<<< orphan*/  st_blksize; } ;
struct kstat {int /*<<< orphan*/  blksize; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 scalar_t__ IS_ERR (struct p9_stat_dotl*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_STATS_ALL ; 
 int PTR_ERR (struct p9_stat_dotl*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int /*<<< orphan*/  kfree (struct p9_stat_dotl*) ; 
 struct p9_stat_dotl* p9_client_getattr_dotl (struct p9_stat_dotl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct dentry*) ; 
 struct v9fs_session_info* v9fs_dentry2v9ses (struct dentry*) ; 
 struct p9_stat_dotl* v9fs_fid_lookup (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_stat2inode_dotl (struct p9_stat_dotl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
v9fs_vfs_getattr_dotl(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int flags)
{
	struct dentry *dentry = path->dentry;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;
	struct p9_stat_dotl *st;

	p9_debug(P9_DEBUG_VFS, "dentry: %p\n", dentry);
	v9ses = v9fs_dentry2v9ses(dentry);
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) {
		generic_fillattr(d_inode(dentry), stat);
		return 0;
	}
	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid))
		return PTR_ERR(fid);

	/* Ask for all the fields in stat structure. Server will return
	 * whatever it supports
	 */

	st = p9_client_getattr_dotl(fid, P9_STATS_ALL);
	if (IS_ERR(st))
		return PTR_ERR(st);

	v9fs_stat2inode_dotl(st, d_inode(dentry), 0);
	generic_fillattr(d_inode(dentry), stat);
	/* Change block size to what the server returned */
	stat->blksize = st->st_blksize;

	kfree(st);
	return 0;
}