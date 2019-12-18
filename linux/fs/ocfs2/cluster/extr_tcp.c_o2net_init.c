#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct o2net_node {int /*<<< orphan*/  nn_status_list; int /*<<< orphan*/  nn_status_idr; int /*<<< orphan*/  nn_sc_wq; int /*<<< orphan*/  nn_persistent_error; int /*<<< orphan*/  nn_still_up; int /*<<< orphan*/  nn_connect_expired; int /*<<< orphan*/  nn_connect_work; int /*<<< orphan*/  nn_lock; int /*<<< orphan*/  nn_timeout; } ;
struct o2net_msg {int dummy; } ;
struct o2net_handshake {int dummy; } ;
struct TYPE_6__ {void* magic; void* connector_id; void* protocol_version; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O2NET_MSG_KEEP_REQ_MAGIC ; 
 int /*<<< orphan*/  O2NET_MSG_KEEP_RESP_MAGIC ; 
 int O2NET_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_connect_expired ; 
 int /*<<< orphan*/  o2net_debugfs_exit () ; 
 int /*<<< orphan*/  o2net_debugfs_init () ; 
 TYPE_1__* o2net_hand ; 
 TYPE_1__* o2net_keep_req ; 
 TYPE_1__* o2net_keep_resp ; 
 struct o2net_node* o2net_nn_from_num (unsigned long) ; 
 int /*<<< orphan*/  o2net_nodes ; 
 int /*<<< orphan*/  o2net_start_connect ; 
 int /*<<< orphan*/  o2net_still_up ; 
 int /*<<< orphan*/  o2quo_exit () ; 
 int /*<<< orphan*/  o2quo_init () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int o2net_init(void)
{
	unsigned long i;

	o2quo_init();

	o2net_debugfs_init();

	o2net_hand = kzalloc(sizeof(struct o2net_handshake), GFP_KERNEL);
	o2net_keep_req = kzalloc(sizeof(struct o2net_msg), GFP_KERNEL);
	o2net_keep_resp = kzalloc(sizeof(struct o2net_msg), GFP_KERNEL);
	if (!o2net_hand || !o2net_keep_req || !o2net_keep_resp)
		goto out;

	o2net_hand->protocol_version = cpu_to_be64(O2NET_PROTOCOL_VERSION);
	o2net_hand->connector_id = cpu_to_be64(1);

	o2net_keep_req->magic = cpu_to_be16(O2NET_MSG_KEEP_REQ_MAGIC);
	o2net_keep_resp->magic = cpu_to_be16(O2NET_MSG_KEEP_RESP_MAGIC);

	for (i = 0; i < ARRAY_SIZE(o2net_nodes); i++) {
		struct o2net_node *nn = o2net_nn_from_num(i);

		atomic_set(&nn->nn_timeout, 0);
		spin_lock_init(&nn->nn_lock);
		INIT_DELAYED_WORK(&nn->nn_connect_work, o2net_start_connect);
		INIT_DELAYED_WORK(&nn->nn_connect_expired,
				  o2net_connect_expired);
		INIT_DELAYED_WORK(&nn->nn_still_up, o2net_still_up);
		/* until we see hb from a node we'll return einval */
		nn->nn_persistent_error = -ENOTCONN;
		init_waitqueue_head(&nn->nn_sc_wq);
		idr_init(&nn->nn_status_idr);
		INIT_LIST_HEAD(&nn->nn_status_list);
	}

	return 0;

out:
	kfree(o2net_hand);
	kfree(o2net_keep_req);
	kfree(o2net_keep_resp);
	o2net_debugfs_exit();
	o2quo_exit();
	return -ENOMEM;
}