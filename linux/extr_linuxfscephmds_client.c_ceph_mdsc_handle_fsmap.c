#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_8__ {int iov_len; void* iov_base; } ;
struct ceph_msg {TYPE_2__ front; } ;
struct ceph_mds_client {int mdsmap_err; int /*<<< orphan*/  mutex; int /*<<< orphan*/  waiting_for_map; struct ceph_fs_client* fsc; } ;
struct ceph_fs_client {TYPE_3__* client; TYPE_1__* mount_options; } ;
struct TYPE_10__ {int fs_cluster_id; } ;
struct TYPE_9__ {TYPE_4__ monc; } ;
struct TYPE_7__ {char* mds_namespace; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_SUB_FSMAP ; 
 int /*<<< orphan*/  CEPH_SUB_MDSMAP ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  __wake_requests (struct ceph_mds_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bad ; 
 int ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_8 (void**) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_monc_got_map (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_monc_renew_subs (TYPE_4__*) ; 
 int /*<<< orphan*/  ceph_monc_want_map (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dout (char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

void ceph_mdsc_handle_fsmap(struct ceph_mds_client *mdsc, struct ceph_msg *msg)
{
	struct ceph_fs_client *fsc = mdsc->fsc;
	const char *mds_namespace = fsc->mount_options->mds_namespace;
	void *p = msg->front.iov_base;
	void *end = p + msg->front.iov_len;
	u32 epoch;
	u32 map_len;
	u32 num_fs;
	u32 mount_fscid = (u32)-1;
	u8 struct_v, struct_cv;
	int err = -EINVAL;

	ceph_decode_need(&p, end, sizeof(u32), bad);
	epoch = ceph_decode_32(&p);

	dout("handle_fsmap epoch %u\n", epoch);

	ceph_decode_need(&p, end, 2 + sizeof(u32), bad);
	struct_v = ceph_decode_8(&p);
	struct_cv = ceph_decode_8(&p);
	map_len = ceph_decode_32(&p);

	ceph_decode_need(&p, end, sizeof(u32) * 3, bad);
	p += sizeof(u32) * 2; /* skip epoch and legacy_client_fscid */

	num_fs = ceph_decode_32(&p);
	while (num_fs-- > 0) {
		void *info_p, *info_end;
		u32 info_len;
		u8 info_v, info_cv;
		u32 fscid, namelen;

		ceph_decode_need(&p, end, 2 + sizeof(u32), bad);
		info_v = ceph_decode_8(&p);
		info_cv = ceph_decode_8(&p);
		info_len = ceph_decode_32(&p);
		ceph_decode_need(&p, end, info_len, bad);
		info_p = p;
		info_end = p + info_len;
		p = info_end;

		ceph_decode_need(&info_p, info_end, sizeof(u32) * 2, bad);
		fscid = ceph_decode_32(&info_p);
		namelen = ceph_decode_32(&info_p);
		ceph_decode_need(&info_p, info_end, namelen, bad);

		if (mds_namespace &&
		    strlen(mds_namespace) == namelen &&
		    !strncmp(mds_namespace, (char *)info_p, namelen)) {
			mount_fscid = fscid;
			break;
		}
	}

	ceph_monc_got_map(&fsc->client->monc, CEPH_SUB_FSMAP, epoch);
	if (mount_fscid != (u32)-1) {
		fsc->client->monc.fs_cluster_id = mount_fscid;
		ceph_monc_want_map(&fsc->client->monc, CEPH_SUB_MDSMAP,
				   0, true);
		ceph_monc_renew_subs(&fsc->client->monc);
	} else {
		err = -ENOENT;
		goto err_out;
	}
	return;

bad:
	pr_err("error decoding fsmap\n");
err_out:
	mutex_lock(&mdsc->mutex);
	mdsc->mdsmap_err = err;
	__wake_requests(mdsc, &mdsc->waiting_for_map);
	mutex_unlock(&mdsc->mutex);
}