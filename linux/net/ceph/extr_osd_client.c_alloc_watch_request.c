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
typedef  int /*<<< orphan*/  u8 ;
struct ceph_osd_request {int dummy; } ;
struct ceph_osd_linger_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct ceph_osd_request* alloc_linger_request (struct ceph_osd_linger_request*) ; 
 scalar_t__ ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  osd_req_op_watch_init (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_osd_request *
alloc_watch_request(struct ceph_osd_linger_request *lreq, u8 watch_opcode)
{
	struct ceph_osd_request *req;

	req = alloc_linger_request(lreq);
	if (!req)
		return NULL;

	/*
	 * Pass 0 for cookie because we don't know it yet, it will be
	 * filled in by linger_submit().
	 */
	osd_req_op_watch_init(req, 0, 0, watch_opcode);

	if (ceph_osdc_alloc_messages(req, GFP_NOIO)) {
		ceph_osdc_put_request(req);
		return NULL;
	}

	return req;
}