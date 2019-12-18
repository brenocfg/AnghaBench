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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  base_oid; int /*<<< orphan*/  base_oloc; } ;
struct ceph_osd_request {TYPE_1__ r_t; int /*<<< orphan*/  r_flags; } ;
struct ceph_osd_client {int dummy; } ;
struct ceph_object_locator {int dummy; } ;
struct ceph_object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_WRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ceph_oid_copy (int /*<<< orphan*/ *,struct ceph_object_id*) ; 
 int /*<<< orphan*/  ceph_oloc_copy (int /*<<< orphan*/ *,struct ceph_object_locator*) ; 
 int ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 struct ceph_osd_request* ceph_osdc_alloc_request (struct ceph_osd_client*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  ceph_osdc_start_request (struct ceph_osd_client*,struct ceph_osd_request*,int) ; 
 int ceph_osdc_wait_request (struct ceph_osd_client*,struct ceph_osd_request*) ; 
 int osd_req_op_copy_from_init (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ceph_object_id*,struct ceph_object_locator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ceph_osdc_copy_from(struct ceph_osd_client *osdc,
			u64 src_snapid, u64 src_version,
			struct ceph_object_id *src_oid,
			struct ceph_object_locator *src_oloc,
			u32 src_fadvise_flags,
			struct ceph_object_id *dst_oid,
			struct ceph_object_locator *dst_oloc,
			u32 dst_fadvise_flags,
			u8 copy_from_flags)
{
	struct ceph_osd_request *req;
	int ret;

	req = ceph_osdc_alloc_request(osdc, NULL, 1, false, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	req->r_flags = CEPH_OSD_FLAG_WRITE;

	ceph_oloc_copy(&req->r_t.base_oloc, dst_oloc);
	ceph_oid_copy(&req->r_t.base_oid, dst_oid);

	ret = osd_req_op_copy_from_init(req, src_snapid, src_version, src_oid,
					src_oloc, src_fadvise_flags,
					dst_fadvise_flags, copy_from_flags);
	if (ret)
		goto out;

	ret = ceph_osdc_alloc_messages(req, GFP_KERNEL);
	if (ret)
		goto out;

	ceph_osdc_start_request(osdc, req, false);
	ret = ceph_osdc_wait_request(osdc, req);

out:
	ceph_osdc_put_request(req);
	return ret;
}