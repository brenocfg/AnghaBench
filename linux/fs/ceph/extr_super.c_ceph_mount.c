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
struct super_block {int /*<<< orphan*/  mdsc; int /*<<< orphan*/  client; } ;
struct file_system_type {int dummy; } ;
struct dentry {int /*<<< orphan*/  mdsc; int /*<<< orphan*/  client; } ;
struct ceph_options {int dummy; } ;
struct ceph_mount_options {int dummy; } ;
struct ceph_fs_client {int /*<<< orphan*/  mdsc; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 struct super_block* ERR_CAST (struct super_block*) ; 
 struct super_block* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  NOSHARE ; 
 struct super_block* PTR_ERR (struct super_block*) ; 
 int SB_POSIXACL ; 
 int ceph_compare_super (struct super_block*,void*) ; 
 int /*<<< orphan*/  ceph_mdsc_close_sessions (int /*<<< orphan*/ ) ; 
 int ceph_mdsc_init (struct super_block*) ; 
 struct super_block* ceph_real_mount (struct super_block*) ; 
 struct super_block* ceph_sb_to_client (struct super_block*) ; 
 int /*<<< orphan*/  ceph_set_super ; 
 int ceph_setup_bdi (struct super_block*,struct super_block*) ; 
 scalar_t__ ceph_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_vinop (int /*<<< orphan*/ ) ; 
 struct super_block* create_fs_client (struct ceph_mount_options*,struct ceph_options*) ; 
 int /*<<< orphan*/  d_inode (struct super_block*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  destroy_fs_client (struct super_block*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int parse_mount_options (struct ceph_mount_options**,struct ceph_options**,int,void*,char const*) ; 
 struct super_block* sget (struct file_system_type*,int (*) (struct super_block*,void*),int /*<<< orphan*/ ,int,struct super_block*) ; 

__attribute__((used)) static struct dentry *ceph_mount(struct file_system_type *fs_type,
		       int flags, const char *dev_name, void *data)
{
	struct super_block *sb;
	struct ceph_fs_client *fsc;
	struct dentry *res;
	int err;
	int (*compare_super)(struct super_block *, void *) = ceph_compare_super;
	struct ceph_mount_options *fsopt = NULL;
	struct ceph_options *opt = NULL;

	dout("ceph_mount\n");

#ifdef CONFIG_CEPH_FS_POSIX_ACL
	flags |= SB_POSIXACL;
#endif
	err = parse_mount_options(&fsopt, &opt, flags, data, dev_name);
	if (err < 0) {
		res = ERR_PTR(err);
		goto out_final;
	}

	/* create client (which we may/may not use) */
	fsc = create_fs_client(fsopt, opt);
	if (IS_ERR(fsc)) {
		res = ERR_CAST(fsc);
		goto out_final;
	}

	err = ceph_mdsc_init(fsc);
	if (err < 0) {
		res = ERR_PTR(err);
		goto out;
	}

	if (ceph_test_opt(fsc->client, NOSHARE))
		compare_super = NULL;
	sb = sget(fs_type, compare_super, ceph_set_super, flags, fsc);
	if (IS_ERR(sb)) {
		res = ERR_CAST(sb);
		goto out;
	}

	if (ceph_sb_to_client(sb) != fsc) {
		destroy_fs_client(fsc);
		fsc = ceph_sb_to_client(sb);
		dout("get_sb got existing client %p\n", fsc);
	} else {
		dout("get_sb using new client %p\n", fsc);
		err = ceph_setup_bdi(sb, fsc);
		if (err < 0) {
			res = ERR_PTR(err);
			goto out_splat;
		}
	}

	res = ceph_real_mount(fsc);
	if (IS_ERR(res))
		goto out_splat;
	dout("root %p inode %p ino %llx.%llx\n", res,
	     d_inode(res), ceph_vinop(d_inode(res)));
	return res;

out_splat:
	ceph_mdsc_close_sessions(fsc->mdsc);
	deactivate_locked_super(sb);
	goto out_final;

out:
	destroy_fs_client(fsc);
out_final:
	dout("ceph_mount fail %ld\n", PTR_ERR(res));
	return res;
}