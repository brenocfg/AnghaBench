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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_osd_request {int /*<<< orphan*/  r_flags; int /*<<< orphan*/  r_base_oloc; int /*<<< orphan*/  r_base_oid; } ;
struct ceph_osd_client {int dummy; } ;
struct ceph_object_locator {int dummy; } ;
struct ceph_object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_READ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  ceph_oid_copy (int /*<<< orphan*/ *,struct ceph_object_id*) ; 
 int /*<<< orphan*/  ceph_oloc_copy (int /*<<< orphan*/ *,struct ceph_object_locator*) ; 
 int ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 struct ceph_osd_request* ceph_osdc_alloc_request (struct ceph_osd_client*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  ceph_osdc_start_request (struct ceph_osd_client*,struct ceph_osd_request*,int) ; 
 int ceph_osdc_wait_request (struct ceph_osd_client*,struct ceph_osd_request*) ; 
 int osd_req_op_notify_ack_init (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int ceph_osdc_notify_ack(struct ceph_osd_client *osdc,
			 struct ceph_object_id *oid,
			 struct ceph_object_locator *oloc,
			 u64 notify_id,
			 u64 cookie,
			 void *payload,
			 u32 payload_len)
{
	struct ceph_osd_request *req;
	int ret;

	req = ceph_osdc_alloc_request(osdc, NULL, 1, false, GFP_NOIO);
	if (!req)
		return -ENOMEM;

	ceph_oid_copy(&req->r_base_oid, oid);
	ceph_oloc_copy(&req->r_base_oloc, oloc);
	req->r_flags = CEPH_OSD_FLAG_READ;

	ret = osd_req_op_notify_ack_init(req, 0, notify_id, cookie, payload,
					 payload_len);
	if (ret)
		goto out_put_req;

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	if (ret)
		goto out_put_req;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_wait_request(osdc, req);

out_put_req:
	ceph_osdc_put_request(req);
	return ret;
}