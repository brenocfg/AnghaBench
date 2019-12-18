#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct ceph_msg {TYPE_1__ front; } ;
struct TYPE_17__ {int /*<<< orphan*/  peer_addr; } ;
struct ceph_mon_client {TYPE_8__* client; int /*<<< orphan*/  mutex; TYPE_7__ con; int /*<<< orphan*/  cur_mon; TYPE_9__* auth; TYPE_3__* m_auth; scalar_t__ pending_auth; } ;
struct TYPE_19__ {int /*<<< orphan*/  global_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  num; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {TYPE_4__ name; } ;
struct TYPE_16__ {TYPE_5__ inst; } ;
struct TYPE_18__ {int auth_err; int /*<<< orphan*/  auth_wq; TYPE_6__ msgr; } ;
struct TYPE_12__ {int /*<<< orphan*/  iov_base; } ;
struct TYPE_13__ {int /*<<< orphan*/  front_alloc_len; TYPE_2__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_ENTITY_TYPE_CLIENT ; 
 int /*<<< orphan*/  __resend_generic_request (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  __send_prepared_auth_request (struct ceph_mon_client*,int) ; 
 int /*<<< orphan*/  __send_subscribe (struct ceph_mon_client*) ; 
 int ceph_auth_is_authenticated (TYPE_9__*) ; 
 int ceph_handle_auth_reply (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_pr_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  finish_hunting (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_auth_reply(struct ceph_mon_client *monc,
			      struct ceph_msg *msg)
{
	int ret;
	int was_auth = 0;

	mutex_lock(&monc->mutex);
	was_auth = ceph_auth_is_authenticated(monc->auth);
	monc->pending_auth = 0;
	ret = ceph_handle_auth_reply(monc->auth, msg->front.iov_base,
				     msg->front.iov_len,
				     monc->m_auth->front.iov_base,
				     monc->m_auth->front_alloc_len);
	if (ret > 0) {
		__send_prepared_auth_request(monc, ret);
		goto out;
	}

	finish_hunting(monc);

	if (ret < 0) {
		monc->client->auth_err = ret;
	} else if (!was_auth && ceph_auth_is_authenticated(monc->auth)) {
		dout("authenticated, starting session\n");

		monc->client->msgr.inst.name.type = CEPH_ENTITY_TYPE_CLIENT;
		monc->client->msgr.inst.name.num =
					cpu_to_le64(monc->auth->global_id);

		__send_subscribe(monc);
		__resend_generic_request(monc);

		pr_info("mon%d %s session established\n", monc->cur_mon,
			ceph_pr_addr(&monc->con.peer_addr));
	}

out:
	mutex_unlock(&monc->mutex);
	if (monc->client->auth_err < 0)
		wake_up_all(&monc->client->auth_wq);
}