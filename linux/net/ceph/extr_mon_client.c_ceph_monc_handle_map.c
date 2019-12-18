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
struct TYPE_3__ {int iov_len; void* iov_base; } ;
struct ceph_msg {TYPE_1__ front; } ;
struct ceph_monmap {int /*<<< orphan*/  epoch; int /*<<< orphan*/  fsid; } ;
struct ceph_mon_client {int /*<<< orphan*/  mutex; struct ceph_monmap* monmap; struct ceph_client* client; } ;
struct TYPE_4__ {struct ceph_monmap* monmap; } ;
struct ceph_client {int have_fsid; int /*<<< orphan*/  auth_wq; TYPE_2__ monc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_SUB_MONMAP ; 
 scalar_t__ IS_ERR (struct ceph_monmap*) ; 
 scalar_t__ PTR_ERR (struct ceph_monmap*) ; 
 int /*<<< orphan*/  __ceph_monc_got_map (struct ceph_mon_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_check_fsid (struct ceph_client*,int /*<<< orphan*/ *) ; 
 struct ceph_monmap* ceph_monmap_decode (void*,void*) ; 
 int /*<<< orphan*/  ceph_msg_dump (struct ceph_msg*) ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  kfree (struct ceph_monmap*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ceph_monc_handle_map(struct ceph_mon_client *monc,
				 struct ceph_msg *msg)
{
	struct ceph_client *client = monc->client;
	struct ceph_monmap *monmap = NULL, *old = monc->monmap;
	void *p, *end;

	mutex_lock(&monc->mutex);

	dout("handle_monmap\n");
	p = msg->front.iov_base;
	end = p + msg->front.iov_len;

	monmap = ceph_monmap_decode(p, end);
	if (IS_ERR(monmap)) {
		pr_err("problem decoding monmap, %d\n",
		       (int)PTR_ERR(monmap));
		ceph_msg_dump(msg);
		goto out;
	}

	if (ceph_check_fsid(monc->client, &monmap->fsid) < 0) {
		kfree(monmap);
		goto out;
	}

	client->monc.monmap = monmap;
	kfree(old);

	__ceph_monc_got_map(monc, CEPH_SUB_MONMAP, monc->monmap->epoch);
	client->have_fsid = true;

out:
	mutex_unlock(&monc->mutex);
	wake_up_all(&client->auth_wq);
}