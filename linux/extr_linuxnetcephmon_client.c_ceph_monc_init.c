#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ceph_mon_subscribe_ack {int dummy; } ;
struct ceph_mon_client {int cur_mon; int had_a_connection; int hunt_mult; int /*<<< orphan*/ * monmap; TYPE_2__* auth; void* m_subscribe_ack; void* m_subscribe; void* m_auth_reply; int /*<<< orphan*/  fs_cluster_id; scalar_t__ last_tid; int /*<<< orphan*/  generic_request_tree; int /*<<< orphan*/  delayed_work; struct ceph_client* client; int /*<<< orphan*/  con; void* m_auth; scalar_t__ pending_auth; int /*<<< orphan*/  mutex; } ;
struct ceph_client {int /*<<< orphan*/  msgr; TYPE_1__* options; } ;
struct TYPE_7__ {int want_keys; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CEPH_ENTITY_TYPE_AUTH ; 
 int CEPH_ENTITY_TYPE_MDS ; 
 int CEPH_ENTITY_TYPE_MON ; 
 int CEPH_ENTITY_TYPE_OSD ; 
 int /*<<< orphan*/  CEPH_FS_CLUSTER_ID_NONE ; 
 int /*<<< orphan*/  CEPH_MSG_AUTH ; 
 int /*<<< orphan*/  CEPH_MSG_AUTH_REPLY ; 
 int /*<<< orphan*/  CEPH_MSG_MON_SUBSCRIBE ; 
 int /*<<< orphan*/  CEPH_MSG_MON_SUBSCRIBE_ACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int build_initial_monmap (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  ceph_auth_destroy (TYPE_2__*) ; 
 TYPE_2__* ceph_auth_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_con_init (int /*<<< orphan*/ *,struct ceph_mon_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_msg_put (void*) ; 
 int /*<<< orphan*/  delayed_work ; 
 int /*<<< orphan*/  dout (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ceph_mon_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mon_con_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int ceph_monc_init(struct ceph_mon_client *monc, struct ceph_client *cl)
{
	int err = 0;

	dout("init\n");
	memset(monc, 0, sizeof(*monc));
	monc->client = cl;
	monc->monmap = NULL;
	mutex_init(&monc->mutex);

	err = build_initial_monmap(monc);
	if (err)
		goto out;

	/* connection */
	/* authentication */
	monc->auth = ceph_auth_init(cl->options->name,
				    cl->options->key);
	if (IS_ERR(monc->auth)) {
		err = PTR_ERR(monc->auth);
		goto out_monmap;
	}
	monc->auth->want_keys =
		CEPH_ENTITY_TYPE_AUTH | CEPH_ENTITY_TYPE_MON |
		CEPH_ENTITY_TYPE_OSD | CEPH_ENTITY_TYPE_MDS;

	/* msgs */
	err = -ENOMEM;
	monc->m_subscribe_ack = ceph_msg_new(CEPH_MSG_MON_SUBSCRIBE_ACK,
				     sizeof(struct ceph_mon_subscribe_ack),
				     GFP_KERNEL, true);
	if (!monc->m_subscribe_ack)
		goto out_auth;

	monc->m_subscribe = ceph_msg_new(CEPH_MSG_MON_SUBSCRIBE, 128,
					 GFP_KERNEL, true);
	if (!monc->m_subscribe)
		goto out_subscribe_ack;

	monc->m_auth_reply = ceph_msg_new(CEPH_MSG_AUTH_REPLY, 4096,
					  GFP_KERNEL, true);
	if (!monc->m_auth_reply)
		goto out_subscribe;

	monc->m_auth = ceph_msg_new(CEPH_MSG_AUTH, 4096, GFP_KERNEL, true);
	monc->pending_auth = 0;
	if (!monc->m_auth)
		goto out_auth_reply;

	ceph_con_init(&monc->con, monc, &mon_con_ops,
		      &monc->client->msgr);

	monc->cur_mon = -1;
	monc->had_a_connection = false;
	monc->hunt_mult = 1;

	INIT_DELAYED_WORK(&monc->delayed_work, delayed_work);
	monc->generic_request_tree = RB_ROOT;
	monc->last_tid = 0;

	monc->fs_cluster_id = CEPH_FS_CLUSTER_ID_NONE;

	return 0;

out_auth_reply:
	ceph_msg_put(monc->m_auth_reply);
out_subscribe:
	ceph_msg_put(monc->m_subscribe);
out_subscribe_ack:
	ceph_msg_put(monc->m_subscribe_ack);
out_auth:
	ceph_auth_destroy(monc->auth);
out_monmap:
	kfree(monc->monmap);
out:
	return err;
}