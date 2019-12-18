#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ceph_mon_generic_request {TYPE_2__* request; void* reply; } ;
struct TYPE_7__ {scalar_t__ session_mon_tid; int /*<<< orphan*/  session_mon; scalar_t__ have_version; } ;
struct ceph_mon_command {void* str_len; int /*<<< orphan*/  str; void* num_strs; int /*<<< orphan*/  fsid; TYPE_3__ monhdr; } ;
struct ceph_mon_client {int /*<<< orphan*/  client; int /*<<< orphan*/  mutex; TYPE_4__* monmap; } ;
struct ceph_entity_addr {int /*<<< orphan*/  nonce; int /*<<< orphan*/  in_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  fsid; } ;
struct TYPE_5__ {struct ceph_mon_command* iov_base; } ;
struct TYPE_6__ {TYPE_1__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MSG_MON_COMMAND ; 
 int /*<<< orphan*/  CEPH_MSG_MON_COMMAND_ACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct ceph_mon_generic_request* alloc_generic_request (struct ceph_mon_client*,int /*<<< orphan*/ ) ; 
 void* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int ceph_wait_for_latest_osdmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_generic_request (struct ceph_mon_generic_request*) ; 
 int /*<<< orphan*/  register_generic_request (struct ceph_mon_generic_request*) ; 
 int /*<<< orphan*/  send_generic_request (struct ceph_mon_client*,struct ceph_mon_generic_request*) ; 
 int sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int wait_generic_request (struct ceph_mon_generic_request*) ; 

int ceph_monc_blacklist_add(struct ceph_mon_client *monc,
			    struct ceph_entity_addr *client_addr)
{
	struct ceph_mon_generic_request *req;
	struct ceph_mon_command *h;
	int ret = -ENOMEM;
	int len;

	req = alloc_generic_request(monc, GFP_NOIO);
	if (!req)
		goto out;

	req->request = ceph_msg_new(CEPH_MSG_MON_COMMAND, 256, GFP_NOIO, true);
	if (!req->request)
		goto out;

	req->reply = ceph_msg_new(CEPH_MSG_MON_COMMAND_ACK, 512, GFP_NOIO,
				  true);
	if (!req->reply)
		goto out;

	mutex_lock(&monc->mutex);
	register_generic_request(req);
	h = req->request->front.iov_base;
	h->monhdr.have_version = 0;
	h->monhdr.session_mon = cpu_to_le16(-1);
	h->monhdr.session_mon_tid = 0;
	h->fsid = monc->monmap->fsid;
	h->num_strs = cpu_to_le32(1);
	len = sprintf(h->str, "{ \"prefix\": \"osd blacklist\", \
		                 \"blacklistop\": \"add\", \
				 \"addr\": \"%pISpc/%u\" }",
		      &client_addr->in_addr, le32_to_cpu(client_addr->nonce));
	h->str_len = cpu_to_le32(len);
	send_generic_request(monc, req);
	mutex_unlock(&monc->mutex);

	ret = wait_generic_request(req);
	if (!ret)
		/*
		 * Make sure we have the osdmap that includes the blacklist
		 * entry.  This is needed to ensure that the OSDs pick up the
		 * new blacklist before processing any future requests from
		 * this client.
		 */
		ret = ceph_wait_for_latest_osdmap(monc->client, 0);

out:
	put_generic_request(req);
	return ret;
}