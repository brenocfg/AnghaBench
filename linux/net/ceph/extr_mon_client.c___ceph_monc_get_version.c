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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_mon_generic_request {int /*<<< orphan*/  tid; TYPE_2__* request; int /*<<< orphan*/  private_data; int /*<<< orphan*/  complete_cb; void* reply; } ;
struct ceph_mon_client {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  ceph_monc_callback_t ;
struct TYPE_3__ {void* iov_base; } ;
struct TYPE_4__ {int front_alloc_len; TYPE_1__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MSG_MON_GET_VERSION ; 
 int /*<<< orphan*/  CEPH_MSG_MON_GET_VERSION_REPLY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ceph_mon_generic_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ceph_mon_generic_request* alloc_generic_request (struct ceph_mon_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_string (void**,void* const,char const*,int) ; 
 void* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_generic_request (struct ceph_mon_generic_request*) ; 
 int /*<<< orphan*/  register_generic_request (struct ceph_mon_generic_request*) ; 
 int /*<<< orphan*/  send_generic_request (struct ceph_mon_client*,struct ceph_mon_generic_request*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct ceph_mon_generic_request *
__ceph_monc_get_version(struct ceph_mon_client *monc, const char *what,
			ceph_monc_callback_t cb, u64 private_data)
{
	struct ceph_mon_generic_request *req;

	req = alloc_generic_request(monc, GFP_NOIO);
	if (!req)
		goto err_put_req;

	req->request = ceph_msg_new(CEPH_MSG_MON_GET_VERSION,
				    sizeof(u64) + sizeof(u32) + strlen(what),
				    GFP_NOIO, true);
	if (!req->request)
		goto err_put_req;

	req->reply = ceph_msg_new(CEPH_MSG_MON_GET_VERSION_REPLY, 32, GFP_NOIO,
				  true);
	if (!req->reply)
		goto err_put_req;

	req->complete_cb = cb;
	req->private_data = private_data;

	mutex_lock(&monc->mutex);
	register_generic_request(req);
	{
		void *p = req->request->front.iov_base;
		void *const end = p + req->request->front_alloc_len;

		ceph_encode_64(&p, req->tid); /* handle */
		ceph_encode_string(&p, end, what, strlen(what));
		WARN_ON(p != end);
	}
	send_generic_request(monc, req);
	mutex_unlock(&monc->mutex);

	return req;

err_put_req:
	put_generic_request(req);
	return ERR_PTR(-ENOMEM);
}