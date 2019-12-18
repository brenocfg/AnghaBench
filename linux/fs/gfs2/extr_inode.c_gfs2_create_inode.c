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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct qstr {scalar_t__ len; } ;
struct posix_acl {int dummy; } ;
struct inode {int i_mode; unsigned int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_rdev; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_root_dir; int /*<<< orphan*/  sd_vfs; } ;
struct gfs2_holder {struct gfs2_glock* gh_gl; } ;
struct gfs2_inode {int i_diskflags; int i_entries; int /*<<< orphan*/  i_flags; struct gfs2_glock* i_gl; struct gfs2_holder i_iopen_gh; int /*<<< orphan*/  i_inode; scalar_t__ i_no_addr; scalar_t__ i_eattr; scalar_t__ i_depth; scalar_t__ i_height; int /*<<< orphan*/  i_goal; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_work; } ;
struct gfs2_diradd {int save_loc; int /*<<< orphan*/ * bh; } ;
struct file {int /*<<< orphan*/  f_mode; } ;
struct dentry {struct qstr d_name; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CREATE ; 
 int /*<<< orphan*/  EISDIR ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMODE_CREATED ; 
 int /*<<< orphan*/  GFS2_AF_ORLOV ; 
 int GFS2_DIF_INHERIT_JDATA ; 
 int GFS2_DIF_JDATA ; 
 int GFS2_DIF_SYSTEM ; 
 int GFS2_DIF_TOPDIR ; 
 scalar_t__ GFS2_FNAMESIZE ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIF_ALLOC_FAILED ; 
 int /*<<< orphan*/  GIF_FREE_VFS_INODE ; 
 int /*<<< orphan*/  GLF_INODE_CREATING ; 
 int /*<<< orphan*/  GL_EXACT ; 
 int /*<<< orphan*/  GL_SKIP ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int PTR_ERR (struct inode*) ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int __gfs2_set_acl (struct inode*,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int alloc_dinode (struct gfs2_inode*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  check_and_update_goal (struct gfs2_inode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int create_ok (struct gfs2_inode*,struct qstr const*,int) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int finish_no_open (struct file*,int /*<<< orphan*/ *) ; 
 int finish_open (struct file*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_dir_no_add (struct gfs2_diradd*) ; 
 struct inode* gfs2_dir_search (struct inode*,struct qstr*,int) ; 
 int gfs2_diradd_alloc_required (struct inode*,struct qstr const*,struct gfs2_diradd*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_get (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gfs2_glock**) ; 
 int gfs2_glock_nq_init (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_put (struct gfs2_glock*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_mark_uninitialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_init_xattr (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_initxattrs ; 
 int /*<<< orphan*/  gfs2_inode_glops ; 
 int /*<<< orphan*/  gfs2_iopen_glops ; 
 int /*<<< orphan*/  gfs2_open_common ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_rsqa_delete (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_set_aops (struct inode*) ; 
 int /*<<< orphan*/  gfs2_set_inode_blocks (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  gfs2_set_iop (struct inode*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_tune_get (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glock_clear_object (struct gfs2_glock*,struct gfs2_inode*) ; 
 int /*<<< orphan*/  glock_set_object (struct gfs2_glock*,struct gfs2_inode*) ; 
 int /*<<< orphan*/  gt_new_files_jdata ; 
 int /*<<< orphan*/  init_dinode (struct gfs2_inode*,struct gfs2_inode*,char const*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int link_dinode (struct gfs2_inode*,struct qstr const*,struct gfs2_inode*,struct gfs2_diradd*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  munge_mode_uid_gid (struct gfs2_inode*,struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int posix_acl_create (struct inode*,int*,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int security_inode_init_security (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qstr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_create_inode(struct inode *dir, struct dentry *dentry,
			     struct file *file,
			     umode_t mode, dev_t dev, const char *symname,
			     unsigned int size, int excl)
{
	const struct qstr *name = &dentry->d_name;
	struct posix_acl *default_acl, *acl;
	struct gfs2_holder ghs[2];
	struct inode *inode = NULL;
	struct gfs2_inode *dip = GFS2_I(dir), *ip;
	struct gfs2_sbd *sdp = GFS2_SB(&dip->i_inode);
	struct gfs2_glock *io_gl = NULL;
	int error, free_vfs_inode = 1;
	u32 aflags = 0;
	unsigned blocks = 1;
	struct gfs2_diradd da = { .bh = NULL, .save_loc = 1, };

	if (!name->len || name->len > GFS2_FNAMESIZE)
		return -ENAMETOOLONG;

	error = gfs2_rsqa_alloc(dip);
	if (error)
		return error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_EXCLUSIVE, 0, ghs);
	if (error)
		goto fail;
	gfs2_holder_mark_uninitialized(ghs + 1);

	error = create_ok(dip, name, mode);
	if (error)
		goto fail_gunlock;

	inode = gfs2_dir_search(dir, &dentry->d_name, !S_ISREG(mode) || excl);
	error = PTR_ERR(inode);
	if (!IS_ERR(inode)) {
		if (S_ISDIR(inode->i_mode)) {
			iput(inode);
			inode = ERR_PTR(-EISDIR);
			goto fail_gunlock;
		}
		d_instantiate(dentry, inode);
		error = 0;
		if (file) {
			if (S_ISREG(inode->i_mode))
				error = finish_open(file, dentry, gfs2_open_common);
			else
				error = finish_no_open(file, NULL);
		}
		gfs2_glock_dq_uninit(ghs);
		return error;
	} else if (error != -ENOENT) {
		goto fail_gunlock;
	}

	error = gfs2_diradd_alloc_required(dir, name, &da);
	if (error < 0)
		goto fail_gunlock;

	inode = new_inode(sdp->sd_vfs);
	error = -ENOMEM;
	if (!inode)
		goto fail_gunlock;

	error = posix_acl_create(dir, &mode, &default_acl, &acl);
	if (error)
		goto fail_gunlock;

	ip = GFS2_I(inode);
	error = gfs2_rsqa_alloc(ip);
	if (error)
		goto fail_free_acls;

	inode->i_mode = mode;
	set_nlink(inode, S_ISDIR(mode) ? 2 : 1);
	inode->i_rdev = dev;
	inode->i_size = size;
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	gfs2_set_inode_blocks(inode, 1);
	munge_mode_uid_gid(dip, inode);
	check_and_update_goal(dip);
	ip->i_goal = dip->i_goal;
	ip->i_diskflags = 0;
	ip->i_eattr = 0;
	ip->i_height = 0;
	ip->i_depth = 0;
	ip->i_entries = 0;
	ip->i_no_addr = 0; /* Temporarily zero until real addr is assigned */

	switch(mode & S_IFMT) {
	case S_IFREG:
		if ((dip->i_diskflags & GFS2_DIF_INHERIT_JDATA) ||
		    gfs2_tune_get(sdp, gt_new_files_jdata))
			ip->i_diskflags |= GFS2_DIF_JDATA;
		gfs2_set_aops(inode);
		break;
	case S_IFDIR:
		ip->i_diskflags |= (dip->i_diskflags & GFS2_DIF_INHERIT_JDATA);
		ip->i_diskflags |= GFS2_DIF_JDATA;
		ip->i_entries = 2;
		break;
	}

	/* Force SYSTEM flag on all files and subdirs of a SYSTEM directory */
	if (dip->i_diskflags & GFS2_DIF_SYSTEM)
		ip->i_diskflags |= GFS2_DIF_SYSTEM;

	gfs2_set_inode_flags(inode);

	if ((GFS2_I(d_inode(sdp->sd_root_dir)) == dip) ||
	    (dip->i_diskflags & GFS2_DIF_TOPDIR))
		aflags |= GFS2_AF_ORLOV;

	if (default_acl || acl)
		blocks++;

	error = alloc_dinode(ip, aflags, &blocks);
	if (error)
		goto fail_free_inode;

	gfs2_set_inode_blocks(inode, blocks);

	error = gfs2_glock_get(sdp, ip->i_no_addr, &gfs2_inode_glops, CREATE, &ip->i_gl);
	if (error)
		goto fail_free_inode;
	flush_delayed_work(&ip->i_gl->gl_work);
	glock_set_object(ip->i_gl, ip);

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, GL_SKIP, ghs + 1);
	if (error)
		goto fail_free_inode;

	error = gfs2_trans_begin(sdp, blocks, 0);
	if (error)
		goto fail_gunlock2;

	if (blocks > 1) {
		ip->i_eattr = ip->i_no_addr + 1;
		gfs2_init_xattr(ip);
	}
	init_dinode(dip, ip, symname);
	gfs2_trans_end(sdp);

	error = gfs2_glock_get(sdp, ip->i_no_addr, &gfs2_iopen_glops, CREATE, &io_gl);
	if (error)
		goto fail_gunlock2;

	BUG_ON(test_and_set_bit(GLF_INODE_CREATING, &io_gl->gl_flags));

	error = gfs2_glock_nq_init(io_gl, LM_ST_SHARED, GL_EXACT, &ip->i_iopen_gh);
	if (error)
		goto fail_gunlock2;

	glock_set_object(ip->i_iopen_gh.gh_gl, ip);
	gfs2_glock_put(io_gl);
	gfs2_set_iop(inode);
	insert_inode_hash(inode);

	free_vfs_inode = 0; /* After this point, the inode is no longer
			       considered free. Any failures need to undo
			       the gfs2 structures. */
	if (default_acl) {
		error = __gfs2_set_acl(inode, default_acl, ACL_TYPE_DEFAULT);
		if (error)
			goto fail_gunlock3;
		posix_acl_release(default_acl);
		default_acl = NULL;
	}
	if (acl) {
		error = __gfs2_set_acl(inode, acl, ACL_TYPE_ACCESS);
		if (error)
			goto fail_gunlock3;
		posix_acl_release(acl);
		acl = NULL;
	}

	error = security_inode_init_security(&ip->i_inode, &dip->i_inode, name,
					     &gfs2_initxattrs, NULL);
	if (error)
		goto fail_gunlock3;

	error = link_dinode(dip, name, ip, &da);
	if (error)
		goto fail_gunlock3;

	mark_inode_dirty(inode);
	d_instantiate(dentry, inode);
	if (file) {
		file->f_mode |= FMODE_CREATED;
		error = finish_open(file, dentry, gfs2_open_common);
	}
	gfs2_glock_dq_uninit(ghs);
	gfs2_glock_dq_uninit(ghs + 1);
	clear_bit(GLF_INODE_CREATING, &io_gl->gl_flags);
	return error;

fail_gunlock3:
	glock_clear_object(io_gl, ip);
	gfs2_glock_dq_uninit(&ip->i_iopen_gh);
	gfs2_glock_put(io_gl);
fail_gunlock2:
	if (io_gl)
		clear_bit(GLF_INODE_CREATING, &io_gl->gl_flags);
fail_free_inode:
	if (ip->i_gl) {
		glock_clear_object(ip->i_gl, ip);
		gfs2_glock_put(ip->i_gl);
	}
	gfs2_rsqa_delete(ip, NULL);
fail_free_acls:
	posix_acl_release(default_acl);
	posix_acl_release(acl);
fail_gunlock:
	gfs2_dir_no_add(&da);
	gfs2_glock_dq_uninit(ghs);
	if (!IS_ERR_OR_NULL(inode)) {
		clear_nlink(inode);
		if (!free_vfs_inode)
			mark_inode_dirty(inode);
		set_bit(free_vfs_inode ? GIF_FREE_VFS_INODE : GIF_ALLOC_FAILED,
			&GFS2_I(inode)->i_flags);
		iput(inode);
	}
	if (gfs2_holder_initialized(ghs + 1))
		gfs2_glock_dq_uninit(ghs + 1);
fail:
	return error;
}