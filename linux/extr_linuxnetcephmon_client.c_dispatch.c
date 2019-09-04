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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct ceph_msg {TYPE_1__ hdr; } ;
struct ceph_mon_client {TYPE_2__* client; } ;
struct ceph_connection {struct ceph_mon_client* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* extra_mon_dispatch ) (TYPE_2__*,struct ceph_msg*) ;int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
#define  CEPH_MSG_AUTH_REPLY 134 
#define  CEPH_MSG_MON_COMMAND_ACK 133 
#define  CEPH_MSG_MON_GET_VERSION_REPLY 132 
#define  CEPH_MSG_MON_MAP 131 
#define  CEPH_MSG_MON_SUBSCRIBE_ACK 130 
#define  CEPH_MSG_OSD_MAP 129 
#define  CEPH_MSG_STATFS_REPLY 128 
 int /*<<< orphan*/  ceph_monc_handle_map (struct ceph_mon_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_type_name (int) ; 
 int /*<<< orphan*/  ceph_osdc_handle_map (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_auth_reply (struct ceph_mon_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_command_ack (struct ceph_mon_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_get_version_reply (struct ceph_mon_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_statfs_reply (struct ceph_mon_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_subscribe_ack (struct ceph_mon_client*,struct ceph_msg*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct ceph_msg*) ; 

__attribute__((used)) static void dispatch(struct ceph_connection *con, struct ceph_msg *msg)
{
	struct ceph_mon_client *monc = con->private;
	int type = le16_to_cpu(msg->hdr.type);

	if (!monc)
		return;

	switch (type) {
	case CEPH_MSG_AUTH_REPLY:
		handle_auth_reply(monc, msg);
		break;

	case CEPH_MSG_MON_SUBSCRIBE_ACK:
		handle_subscribe_ack(monc, msg);
		break;

	case CEPH_MSG_STATFS_REPLY:
		handle_statfs_reply(monc, msg);
		break;

	case CEPH_MSG_MON_GET_VERSION_REPLY:
		handle_get_version_reply(monc, msg);
		break;

	case CEPH_MSG_MON_COMMAND_ACK:
		handle_command_ack(monc, msg);
		break;

	case CEPH_MSG_MON_MAP:
		ceph_monc_handle_map(monc, msg);
		break;

	case CEPH_MSG_OSD_MAP:
		ceph_osdc_handle_map(&monc->client->osdc, msg);
		break;

	default:
		/* can the chained handler handle it? */
		if (monc->client->extra_mon_dispatch &&
		    monc->client->extra_mon_dispatch(monc->client, msg) == 0)
			break;

		pr_err("received unknown message type %d %s\n", type,
		       ceph_msg_type_name(type));
	}
	ceph_msg_put(msg);
}