#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int iov_len; void* iov_base; } ;
struct ceph_msg {TYPE_1__ front; } ;
struct ceph_mdsmap {int m_epoch; scalar_t__ m_max_file_size; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; struct ceph_mdsmap* mdsmap; TYPE_2__* fsc; int /*<<< orphan*/  waiting_for_map; } ;
struct ceph_fsid {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  fsid ;
struct TYPE_6__ {int /*<<< orphan*/  monc; } ;
struct TYPE_5__ {TYPE_3__* client; int /*<<< orphan*/  max_file_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_SUB_MDSMAP ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct ceph_mdsmap*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int PTR_ERR (struct ceph_mdsmap*) ; 
 int /*<<< orphan*/  __wake_requests (struct ceph_mds_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bad ; 
 scalar_t__ ceph_check_fsid (TYPE_3__*,struct ceph_fsid*) ; 
 int ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_copy (void**,struct ceph_fsid*,int) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 struct ceph_mdsmap* ceph_mdsmap_decode (void**,void*) ; 
 int /*<<< orphan*/  ceph_mdsmap_destroy (struct ceph_mdsmap*) ; 
 int /*<<< orphan*/  ceph_monc_got_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_new_map (struct ceph_mds_client*,struct ceph_mdsmap*,struct ceph_mdsmap*) ; 
 int /*<<< orphan*/  dout (char*,int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  schedule_delayed (struct ceph_mds_client*) ; 

void ceph_mdsc_handle_mdsmap(struct ceph_mds_client *mdsc, struct ceph_msg *msg)
{
	u32 epoch;
	u32 maplen;
	void *p = msg->front.iov_base;
	void *end = p + msg->front.iov_len;
	struct ceph_mdsmap *newmap, *oldmap;
	struct ceph_fsid fsid;
	int err = -EINVAL;

	ceph_decode_need(&p, end, sizeof(fsid)+2*sizeof(u32), bad);
	ceph_decode_copy(&p, &fsid, sizeof(fsid));
	if (ceph_check_fsid(mdsc->fsc->client, &fsid) < 0)
		return;
	epoch = ceph_decode_32(&p);
	maplen = ceph_decode_32(&p);
	dout("handle_map epoch %u len %d\n", epoch, (int)maplen);

	/* do we need it? */
	mutex_lock(&mdsc->mutex);
	if (mdsc->mdsmap && epoch <= mdsc->mdsmap->m_epoch) {
		dout("handle_map epoch %u <= our %u\n",
		     epoch, mdsc->mdsmap->m_epoch);
		mutex_unlock(&mdsc->mutex);
		return;
	}

	newmap = ceph_mdsmap_decode(&p, end);
	if (IS_ERR(newmap)) {
		err = PTR_ERR(newmap);
		goto bad_unlock;
	}

	/* swap into place */
	if (mdsc->mdsmap) {
		oldmap = mdsc->mdsmap;
		mdsc->mdsmap = newmap;
		check_new_map(mdsc, newmap, oldmap);
		ceph_mdsmap_destroy(oldmap);
	} else {
		mdsc->mdsmap = newmap;  /* first mds map */
	}
	mdsc->fsc->max_file_size = min((loff_t)mdsc->mdsmap->m_max_file_size,
					MAX_LFS_FILESIZE);

	__wake_requests(mdsc, &mdsc->waiting_for_map);
	ceph_monc_got_map(&mdsc->fsc->client->monc, CEPH_SUB_MDSMAP,
			  mdsc->mdsmap->m_epoch);

	mutex_unlock(&mdsc->mutex);
	schedule_delayed(mdsc);
	return;

bad_unlock:
	mutex_unlock(&mdsc->mutex);
bad:
	pr_err("error decoding mdsmap %d\n", err);
	return;
}