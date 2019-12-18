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
struct inode {int i_mode; TYPE_1__* i_fop; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* open ) (struct inode*,struct file*) ;int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  ceph_fscache_file_set_cookie (struct inode*,struct file*) ; 
 int /*<<< orphan*/  ceph_fscache_register_inode_cookie (struct inode*) ; 
 int ceph_init_file_info (struct inode*,struct file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_fmode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_release ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct file*,int) ; 
 int stub1 (struct inode*,struct file*) ; 

__attribute__((used)) static int ceph_init_file(struct inode *inode, struct file *file, int fmode)
{
	int ret = 0;

	switch (inode->i_mode & S_IFMT) {
	case S_IFREG:
		ceph_fscache_register_inode_cookie(inode);
		ceph_fscache_file_set_cookie(inode, file);
		/* fall through */
	case S_IFDIR:
		ret = ceph_init_file_info(inode, file, fmode,
						S_ISDIR(inode->i_mode));
		if (ret)
			return ret;
		break;

	case S_IFLNK:
		dout("init_file %p %p 0%o (symlink)\n", inode, file,
		     inode->i_mode);
		ceph_put_fmode(ceph_inode(inode), fmode); /* clean up */
		break;

	default:
		dout("init_file %p %p 0%o (special)\n", inode, file,
		     inode->i_mode);
		/*
		 * we need to drop the open ref now, since we don't
		 * have .release set to ceph_release.
		 */
		ceph_put_fmode(ceph_inode(inode), fmode); /* clean up */
		BUG_ON(inode->i_fop->release == ceph_release);

		/* call the proper open fop */
		ret = inode->i_fop->open(inode, file);
	}
	return ret;
}