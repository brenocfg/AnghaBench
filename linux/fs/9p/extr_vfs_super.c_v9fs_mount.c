#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct v9fs_session_info {scalar_t__ cache; struct dentry* s_root; int /*<<< orphan*/  qid; int /*<<< orphan*/ * s_d_op; } ;
struct super_block {scalar_t__ cache; struct dentry* s_root; int /*<<< orphan*/  qid; int /*<<< orphan*/ * s_d_op; } ;
struct p9_wstat {scalar_t__ cache; struct dentry* s_root; int /*<<< orphan*/  qid; int /*<<< orphan*/ * s_d_op; } ;
struct p9_stat_dotl {scalar_t__ cache; struct dentry* s_root; int /*<<< orphan*/  qid; int /*<<< orphan*/ * s_d_op; } ;
struct p9_fid {scalar_t__ cache; struct dentry* s_root; int /*<<< orphan*/  qid; int /*<<< orphan*/ * s_d_op; } ;
struct inode {scalar_t__ cache; struct dentry* s_root; int /*<<< orphan*/  qid; int /*<<< orphan*/ * s_d_op; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {void* i_ino; } ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_STATS_BASIC ; 
 int PTR_ERR (struct v9fs_session_info*) ; 
 int S_IFDIR ; 
 int S_IRWXUGO ; 
 int S_ISVTX ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 struct dentry* d_make_root (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct v9fs_session_info*) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  kfree (struct v9fs_session_info*) ; 
 struct v9fs_session_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_client_clunk (struct v9fs_session_info*) ; 
 struct v9fs_session_info* p9_client_getattr_dotl (struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* p9_client_stat (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p9stat_free (struct v9fs_session_info*) ; 
 struct v9fs_session_info* sget (struct file_system_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_cached_dentry_operations ; 
 int /*<<< orphan*/  v9fs_dentry_operations ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct v9fs_session_info*) ; 
 int v9fs_fill_super (struct v9fs_session_info*,struct v9fs_session_info*,int) ; 
 int v9fs_get_acl (struct v9fs_session_info*,struct v9fs_session_info*) ; 
 struct v9fs_session_info* v9fs_get_inode (struct v9fs_session_info*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 
 void* v9fs_qid2ino (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_session_close (struct v9fs_session_info*) ; 
 struct v9fs_session_info* v9fs_session_init (struct v9fs_session_info*,char const*,void*) ; 
 int /*<<< orphan*/  v9fs_set_super ; 
 int /*<<< orphan*/  v9fs_stat2inode (struct v9fs_session_info*,TYPE_1__*,struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_stat2inode_dotl (struct v9fs_session_info*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *v9fs_mount(struct file_system_type *fs_type, int flags,
		       const char *dev_name, void *data)
{
	struct super_block *sb = NULL;
	struct inode *inode = NULL;
	struct dentry *root = NULL;
	struct v9fs_session_info *v9ses = NULL;
	umode_t mode = S_IRWXUGO | S_ISVTX;
	struct p9_fid *fid;
	int retval = 0;

	p9_debug(P9_DEBUG_VFS, "\n");

	v9ses = kzalloc(sizeof(struct v9fs_session_info), GFP_KERNEL);
	if (!v9ses)
		return ERR_PTR(-ENOMEM);

	fid = v9fs_session_init(v9ses, dev_name, data);
	if (IS_ERR(fid)) {
		retval = PTR_ERR(fid);
		goto free_session;
	}

	sb = sget(fs_type, NULL, v9fs_set_super, flags, v9ses);
	if (IS_ERR(sb)) {
		retval = PTR_ERR(sb);
		goto clunk_fid;
	}
	retval = v9fs_fill_super(sb, v9ses, flags);
	if (retval)
		goto release_sb;

	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		sb->s_d_op = &v9fs_cached_dentry_operations;
	else
		sb->s_d_op = &v9fs_dentry_operations;

	inode = v9fs_get_inode(sb, S_IFDIR | mode, 0);
	if (IS_ERR(inode)) {
		retval = PTR_ERR(inode);
		goto release_sb;
	}

	root = d_make_root(inode);
	if (!root) {
		retval = -ENOMEM;
		goto release_sb;
	}
	sb->s_root = root;
	if (v9fs_proto_dotl(v9ses)) {
		struct p9_stat_dotl *st = NULL;
		st = p9_client_getattr_dotl(fid, P9_STATS_BASIC);
		if (IS_ERR(st)) {
			retval = PTR_ERR(st);
			goto release_sb;
		}
		d_inode(root)->i_ino = v9fs_qid2ino(&st->qid);
		v9fs_stat2inode_dotl(st, d_inode(root), 0);
		kfree(st);
	} else {
		struct p9_wstat *st = NULL;
		st = p9_client_stat(fid);
		if (IS_ERR(st)) {
			retval = PTR_ERR(st);
			goto release_sb;
		}

		d_inode(root)->i_ino = v9fs_qid2ino(&st->qid);
		v9fs_stat2inode(st, d_inode(root), sb, 0);

		p9stat_free(st);
		kfree(st);
	}
	retval = v9fs_get_acl(inode, fid);
	if (retval)
		goto release_sb;
	v9fs_fid_add(root, fid);

	p9_debug(P9_DEBUG_VFS, " simple set mount, return 0\n");
	return dget(sb->s_root);

clunk_fid:
	p9_client_clunk(fid);
	v9fs_session_close(v9ses);
free_session:
	kfree(v9ses);
	return ERR_PTR(retval);

release_sb:
	/*
	 * we will do the session_close and root dentry release
	 * in the below call. But we need to clunk fid, because we haven't
	 * attached the fid to dentry so it won't get clunked
	 * automatically.
	 */
	p9_client_clunk(fid);
	deactivate_locked_super(sb);
	return ERR_PTR(retval);
}