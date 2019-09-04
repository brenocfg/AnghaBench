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
struct v9fs_inode {int /*<<< orphan*/  v_mutex; void* writeback_fid; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct p9_fid* private_data; } ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 int /*<<< orphan*/  generic_file_llseek (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_open (struct p9_fid*,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct inode*,struct file*) ; 
 int /*<<< orphan*/  v9fs_cache_inode_set_cookie (struct inode*,struct file*) ; 
 struct p9_fid* v9fs_fid_clone (int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 int v9fs_open_to_dotl_flags (int) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_proto_dotu (struct v9fs_session_info*) ; 
 int v9fs_uflags2omode (int,int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_writeback_fid (int /*<<< orphan*/ ) ; 

int v9fs_file_open(struct inode *inode, struct file *file)
{
	int err;
	struct v9fs_inode *v9inode;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;
	int omode;

	p9_debug(P9_DEBUG_VFS, "inode: %p file: %p\n", inode, file);
	v9inode = V9FS_I(inode);
	v9ses = v9fs_inode2v9ses(inode);
	if (v9fs_proto_dotl(v9ses))
		omode = v9fs_open_to_dotl_flags(file->f_flags);
	else
		omode = v9fs_uflags2omode(file->f_flags,
					v9fs_proto_dotu(v9ses));
	fid = file->private_data;
	if (!fid) {
		fid = v9fs_fid_clone(file_dentry(file));
		if (IS_ERR(fid))
			return PTR_ERR(fid);

		err = p9_client_open(fid, omode);
		if (err < 0) {
			p9_client_clunk(fid);
			return err;
		}
		if ((file->f_flags & O_APPEND) &&
			(!v9fs_proto_dotu(v9ses) && !v9fs_proto_dotl(v9ses)))
			generic_file_llseek(file, 0, SEEK_END);
	}

	file->private_data = fid;
	mutex_lock(&v9inode->v_mutex);
	if ((v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) &&
	    !v9inode->writeback_fid &&
	    ((file->f_flags & O_ACCMODE) != O_RDONLY)) {
		/*
		 * clone a fid and add it to writeback_fid
		 * we do it during open time instead of
		 * page dirty time via write_begin/page_mkwrite
		 * because we want write after unlink usecase
		 * to work.
		 */
		fid = v9fs_writeback_fid(file_dentry(file));
		if (IS_ERR(fid)) {
			err = PTR_ERR(fid);
			mutex_unlock(&v9inode->v_mutex);
			goto out_error;
		}
		v9inode->writeback_fid = (void *) fid;
	}
	mutex_unlock(&v9inode->v_mutex);
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		v9fs_cache_inode_set_cookie(inode, file);
	return 0;
out_error:
	p9_client_clunk(file->private_data);
	file->private_data = NULL;
	return err;
}