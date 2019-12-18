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
struct ovl_cattr {int mode; int /*<<< orphan*/  link; int /*<<< orphan*/  rdev; scalar_t__ hardlink; } ;
struct inode {int dummy; } ;
struct dentry {scalar_t__ d_inode; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 struct dentry* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int ovl_do_create (struct inode*,struct dentry*,int) ; 
 int ovl_do_link (scalar_t__,struct inode*,struct dentry*) ; 
 int ovl_do_mknod (struct inode*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 int ovl_do_symlink (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int ovl_mkdir_real (struct inode*,struct dentry**,int) ; 

struct dentry *ovl_create_real(struct inode *dir, struct dentry *newdentry,
			       struct ovl_cattr *attr)
{
	int err;

	if (IS_ERR(newdentry))
		return newdentry;

	err = -ESTALE;
	if (newdentry->d_inode)
		goto out;

	if (attr->hardlink) {
		err = ovl_do_link(attr->hardlink, dir, newdentry);
	} else {
		switch (attr->mode & S_IFMT) {
		case S_IFREG:
			err = ovl_do_create(dir, newdentry, attr->mode);
			break;

		case S_IFDIR:
			/* mkdir is special... */
			err =  ovl_mkdir_real(dir, &newdentry, attr->mode);
			break;

		case S_IFCHR:
		case S_IFBLK:
		case S_IFIFO:
		case S_IFSOCK:
			err = ovl_do_mknod(dir, newdentry, attr->mode,
					   attr->rdev);
			break;

		case S_IFLNK:
			err = ovl_do_symlink(dir, newdentry, attr->link);
			break;

		default:
			err = -EPERM;
		}
	}
	if (!err && WARN_ON(!newdentry->d_inode)) {
		/*
		 * Not quite sure if non-instantiated dentry is legal or not.
		 * VFS doesn't seem to care so check and warn here.
		 */
		err = -EIO;
	}
out:
	if (err) {
		dput(newdentry);
		return ERR_PTR(err);
	}
	return newdentry;
}