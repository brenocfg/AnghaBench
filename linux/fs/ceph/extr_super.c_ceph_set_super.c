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
struct super_block {int s_time_gran; struct ceph_fs_client* s_fs_info; int /*<<< orphan*/  s_time_max; scalar_t__ s_time_min; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/  s_flags; } ;
struct ceph_fs_client {unsigned long long max_file_size; struct super_block* sb; TYPE_1__* mount_options; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  ceph_dentry_ops ; 
 int /*<<< orphan*/  ceph_export_ops ; 
 int /*<<< orphan*/  ceph_super_ops ; 
 int /*<<< orphan*/  ceph_xattr_handlers ; 
 int /*<<< orphan*/  dout (char*,struct super_block*,void*) ; 
 int set_anon_super (struct super_block*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_set_super(struct super_block *s, void *data)
{
	struct ceph_fs_client *fsc = data;
	int ret;

	dout("set_super %p data %p\n", s, data);

	s->s_flags = fsc->mount_options->sb_flags;
	s->s_maxbytes = MAX_LFS_FILESIZE;

	s->s_xattr = ceph_xattr_handlers;
	s->s_fs_info = fsc;
	fsc->sb = s;
	fsc->max_file_size = 1ULL << 40; /* temp value until we get mdsmap */

	s->s_op = &ceph_super_ops;
	s->s_d_op = &ceph_dentry_ops;
	s->s_export_op = &ceph_export_ops;

	s->s_time_gran = 1;
	s->s_time_min = 0;
	s->s_time_max = U32_MAX;

	ret = set_anon_super(s, NULL);  /* what is that second arg for? */
	if (ret != 0)
		goto fail;

	return ret;

fail:
	s->s_fs_info = NULL;
	fsc->sb = NULL;
	return ret;
}