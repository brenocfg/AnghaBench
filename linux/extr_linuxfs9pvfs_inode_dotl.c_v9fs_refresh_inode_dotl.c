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
struct v9fs_session_info {scalar_t__ cache; } ;
struct p9_stat_dotl {int st_mode; } ;
struct p9_fid {int dummy; } ;
struct inode {int i_mode; } ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 scalar_t__ IS_ERR (struct p9_stat_dotl*) ; 
 int /*<<< orphan*/  P9_STATS_ALL ; 
 int PTR_ERR (struct p9_stat_dotl*) ; 
 int S_IFMT ; 
 unsigned int V9FS_STAT2INODE_KEEP_ISIZE ; 
 int /*<<< orphan*/  kfree (struct p9_stat_dotl*) ; 
 struct p9_stat_dotl* p9_client_getattr_dotl (struct p9_fid*,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 int /*<<< orphan*/  v9fs_stat2inode_dotl (struct p9_stat_dotl*,struct inode*,unsigned int) ; 

int v9fs_refresh_inode_dotl(struct p9_fid *fid, struct inode *inode)
{
	struct p9_stat_dotl *st;
	struct v9fs_session_info *v9ses;
	unsigned int flags;

	v9ses = v9fs_inode2v9ses(inode);
	st = p9_client_getattr_dotl(fid, P9_STATS_ALL);
	if (IS_ERR(st))
		return PTR_ERR(st);
	/*
	 * Don't update inode if the file type is different
	 */
	if ((inode->i_mode & S_IFMT) != (st->st_mode & S_IFMT))
		goto out;

	/*
	 * We don't want to refresh inode->i_size,
	 * because we may have cached data
	 */
	flags = (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) ?
		V9FS_STAT2INODE_KEEP_ISIZE : 0;
	v9fs_stat2inode_dotl(st, inode, flags);
out:
	kfree(st);
	return 0;
}