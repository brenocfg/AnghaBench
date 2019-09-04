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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_auth_client {void* global_id; int negotiating; int protocol; int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
typedef  int s32 ;
struct TYPE_2__ {int (* handle_reply ) (struct ceph_auth_client*,int,void*,void*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* destroy ) (struct ceph_auth_client*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  bad ; 
 int ceph_auth_init_protocol (struct ceph_auth_client*,int) ; 
 int ceph_build_auth_request (struct ceph_auth_client*,void*,size_t) ; 
 void* ceph_decode_32 (void**) ; 
 void* ceph_decode_64 (void**) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,void*,void*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ceph_auth_client*) ; 
 int stub2 (struct ceph_auth_client*,int,void*,void*) ; 

int ceph_handle_auth_reply(struct ceph_auth_client *ac,
			   void *buf, size_t len,
			   void *reply_buf, size_t reply_len)
{
	void *p = buf;
	void *end = buf + len;
	int protocol;
	s32 result;
	u64 global_id;
	void *payload, *payload_end;
	int payload_len;
	char *result_msg;
	int result_msg_len;
	int ret = -EINVAL;

	mutex_lock(&ac->mutex);
	dout("handle_auth_reply %p %p\n", p, end);
	ceph_decode_need(&p, end, sizeof(u32) * 3 + sizeof(u64), bad);
	protocol = ceph_decode_32(&p);
	result = ceph_decode_32(&p);
	global_id = ceph_decode_64(&p);
	payload_len = ceph_decode_32(&p);
	payload = p;
	p += payload_len;
	ceph_decode_need(&p, end, sizeof(u32), bad);
	result_msg_len = ceph_decode_32(&p);
	result_msg = p;
	p += result_msg_len;
	if (p != end)
		goto bad;

	dout(" result %d '%.*s' gid %llu len %d\n", result, result_msg_len,
	     result_msg, global_id, payload_len);

	payload_end = payload + payload_len;

	if (global_id && ac->global_id != global_id) {
		dout(" set global_id %lld -> %lld\n", ac->global_id, global_id);
		ac->global_id = global_id;
	}

	if (ac->negotiating) {
		/* server does not support our protocols? */
		if (!protocol && result < 0) {
			ret = result;
			goto out;
		}
		/* set up (new) protocol handler? */
		if (ac->protocol && ac->protocol != protocol) {
			ac->ops->destroy(ac);
			ac->protocol = 0;
			ac->ops = NULL;
		}
		if (ac->protocol != protocol) {
			ret = ceph_auth_init_protocol(ac, protocol);
			if (ret) {
				pr_err("error %d on auth protocol %d init\n",
				       ret, protocol);
				goto out;
			}
		}

		ac->negotiating = false;
	}

	ret = ac->ops->handle_reply(ac, result, payload, payload_end);
	if (ret == -EAGAIN) {
		ret = ceph_build_auth_request(ac, reply_buf, reply_len);
	} else if (ret) {
		pr_err("auth method '%s' error %d\n", ac->ops->name, ret);
	}

out:
	mutex_unlock(&ac->mutex);
	return ret;

bad:
	pr_err("failed to decode auth msg\n");
	ret = -EINVAL;
	goto out;
}