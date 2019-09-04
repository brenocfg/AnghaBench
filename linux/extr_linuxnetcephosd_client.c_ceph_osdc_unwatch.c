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
struct ceph_osd_request {int /*<<< orphan*/  r_mtime; int /*<<< orphan*/  r_flags; int /*<<< orphan*/  r_base_oloc; int /*<<< orphan*/  r_base_oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  base_oloc; int /*<<< orphan*/  base_oid; } ;
struct ceph_osd_linger_request {int /*<<< orphan*/  linger_id; TYPE_2__ t; } ;
struct ceph_osd_client {TYPE_1__* client; } ;
struct ceph_options {int /*<<< orphan*/  mount_timeout; } ;
struct TYPE_3__ {struct ceph_options* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_WRITE ; 
 int /*<<< orphan*/  CEPH_OSD_WATCH_OP_UNWATCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  ceph_oid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_oloc_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 struct ceph_osd_request* ceph_osdc_alloc_request (struct ceph_osd_client*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  ceph_osdc_start_request (struct ceph_osd_client*,struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linger_cancel (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_put (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  osd_req_op_watch_init (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_request_timeout (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 

int ceph_osdc_unwatch(struct ceph_osd_client *osdc,
		      struct ceph_osd_linger_request *lreq)
{
	struct ceph_options *opts = osdc->client->options;
	struct ceph_osd_request *req;
	int ret;

	req = ceph_osdc_alloc_request(osdc, NULL, 1, false, GFP_NOIO);
	if (!req)
		return -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, &lreq->t.base_oid);
	ceph_oloc_copy(&req->r_base_oloc, &lreq->t.base_oloc);
	req->r_flags = CEPH_OSD_FLAG_WRITE;
	ktime_get_real_ts64(&req->r_mtime);
	osd_req_op_watch_init(req, 0, lreq->linger_id,
			      CEPH_OSD_WATCH_OP_UNWATCH);

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	if (ret)
		goto out_put_req;

	ceph_osdc_start_request(osdc, req, false);
	linger_cancel(lreq);
	linger_put(lreq);
	ret = wait_request_timeout(req, opts->mount_timeout);

out_put_req:
	ceph_osdc_put_request(req);
	return ret;
}