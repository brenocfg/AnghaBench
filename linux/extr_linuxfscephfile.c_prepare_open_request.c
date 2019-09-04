#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ open; } ;
struct ceph_mds_request {TYPE_2__ r_args; int /*<<< orphan*/  r_fmode; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int CEPH_MDS_OP_CREATE ; 
 int CEPH_MDS_OP_OPEN ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int USE_ANY_MDS ; 
 int USE_AUTH_MDS ; 
 int /*<<< orphan*/  ceph_flags_sys2wire (int) ; 
 int /*<<< orphan*/  ceph_flags_to_mode (int) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int,int) ; 
 struct ceph_fs_client* ceph_sb_to_client (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static struct ceph_mds_request *
prepare_open_request(struct super_block *sb, int flags, int create_mode)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	int want_auth = USE_ANY_MDS;
	int op = (flags & O_CREAT) ? CEPH_MDS_OP_CREATE : CEPH_MDS_OP_OPEN;

	if (flags & (O_WRONLY|O_RDWR|O_CREAT|O_TRUNC))
		want_auth = USE_AUTH_MDS;

	req = ceph_mdsc_create_request(mdsc, op, want_auth);
	if (IS_ERR(req))
		goto out;
	req->r_fmode = ceph_flags_to_mode(flags);
	req->r_args.open.flags = ceph_flags_sys2wire(flags);
	req->r_args.open.mode = cpu_to_le32(create_mode);
out:
	return req;
}