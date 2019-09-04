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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  base_oloc; int /*<<< orphan*/  base_oid; } ;
struct ceph_osd_linger_request {size_t* preply_len; int /*<<< orphan*/  reg_req; int /*<<< orphan*/  linger_id; TYPE_1__ t; struct page*** preply_pages; } ;
struct ceph_osd_client {int /*<<< orphan*/  lock; } ;
struct ceph_object_locator {int dummy; } ;
struct ceph_object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_READ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  alloc_linger_request (struct ceph_osd_linger_request*) ; 
 struct page** ceph_alloc_page_vector (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_oid_copy (int /*<<< orphan*/ *,struct ceph_object_id*) ; 
 int /*<<< orphan*/  ceph_oloc_copy (int /*<<< orphan*/ *,struct ceph_object_locator*) ; 
 int /*<<< orphan*/  ceph_osd_data_pages_init (int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ceph_release_page_vector (struct page**,int) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_osd_linger_request*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct ceph_osd_linger_request* linger_alloc (struct ceph_osd_client*) ; 
 int /*<<< orphan*/  linger_cancel (struct ceph_osd_linger_request*) ; 
 int linger_notify_finish_wait (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_put (struct ceph_osd_linger_request*) ; 
 int linger_reg_commit_wait (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_register (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_submit (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  linger_unregister (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  notify ; 
 int /*<<< orphan*/  osd_req_op_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int osd_req_op_notify_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  response_data ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ceph_osdc_notify(struct ceph_osd_client *osdc,
		     struct ceph_object_id *oid,
		     struct ceph_object_locator *oloc,
		     void *payload,
		     u32 payload_len,
		     u32 timeout,
		     struct page ***preply_pages,
		     size_t *preply_len)
{
	struct ceph_osd_linger_request *lreq;
	struct page **pages;
	int ret;

	WARN_ON(!timeout);
	if (preply_pages) {
		*preply_pages = NULL;
		*preply_len = 0;
	}

	lreq = linger_alloc(osdc);
	if (!lreq)
		return -ENOMEM;

	lreq->preply_pages = preply_pages;
	lreq->preply_len = preply_len;

	ceph_oid_copy(&lreq->t.base_oid, oid);
	ceph_oloc_copy(&lreq->t.base_oloc, oloc);
	lreq->t.flags = CEPH_OSD_FLAG_READ;

	lreq->reg_req = alloc_linger_request(lreq);
	if (!lreq->reg_req) {
		ret = -ENOMEM;
		goto out_put_lreq;
	}

	/* for notify_id */
	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	if (IS_ERR(pages)) {
		ret = PTR_ERR(pages);
		goto out_put_lreq;
	}

	down_write(&osdc->lock);
	linger_register(lreq); /* before osd_req_op_* */
	ret = osd_req_op_notify_init(lreq->reg_req, 0, lreq->linger_id, 1,
				     timeout, payload, payload_len);
	if (ret) {
		linger_unregister(lreq);
		up_write(&osdc->lock);
		ceph_release_page_vector(pages, 1);
		goto out_put_lreq;
	}
	ceph_osd_data_pages_init(osd_req_op_data(lreq->reg_req, 0, notify,
						 response_data),
				 pages, PAGE_SIZE, 0, false, true);
	linger_submit(lreq);
	up_write(&osdc->lock);

	ret = linger_reg_commit_wait(lreq);
	if (!ret)
		ret = linger_notify_finish_wait(lreq);
	else
		dout("lreq %p failed to initiate notify %d\n", lreq, ret);

	linger_cancel(lreq);
out_put_lreq:
	linger_put(lreq);
	return ret;
}