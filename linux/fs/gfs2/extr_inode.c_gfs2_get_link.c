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
struct inode {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_dinode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ECHILD ; 
 int EIO ; 
 int ENOMEM ; 
 char const* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_link ; 
 char* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *gfs2_get_link(struct dentry *dentry,
				 struct inode *inode,
				 struct delayed_call *done)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder i_gh;
	struct buffer_head *dibh;
	unsigned int size;
	char *buf;
	int error;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &i_gh);
	error = gfs2_glock_nq(&i_gh);
	if (error) {
		gfs2_holder_uninit(&i_gh);
		return ERR_PTR(error);
	}

	size = (unsigned int)i_size_read(&ip->i_inode);
	if (size == 0) {
		gfs2_consist_inode(ip);
		buf = ERR_PTR(-EIO);
		goto out;
	}

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error) {
		buf = ERR_PTR(error);
		goto out;
	}

	buf = kzalloc(size + 1, GFP_NOFS);
	if (!buf)
		buf = ERR_PTR(-ENOMEM);
	else
		memcpy(buf, dibh->b_data + sizeof(struct gfs2_dinode), size);
	brelse(dibh);
out:
	gfs2_glock_dq_uninit(&i_gh);
	if (!IS_ERR(buf))
		set_delayed_call(done, kfree_link, buf);
	return buf;
}