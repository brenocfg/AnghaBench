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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ceph_msg {TYPE_1__ hdr; } ;
struct ceph_mds_session {struct ceph_mds_client* s_mdsc; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; } ;
struct ceph_connection {struct ceph_mds_session* private; } ;

/* Variables and functions */
#define  CEPH_MSG_CLIENT_CAPS 136 
#define  CEPH_MSG_CLIENT_LEASE 135 
#define  CEPH_MSG_CLIENT_QUOTA 134 
#define  CEPH_MSG_CLIENT_REPLY 133 
#define  CEPH_MSG_CLIENT_REQUEST_FORWARD 132 
#define  CEPH_MSG_CLIENT_SESSION 131 
#define  CEPH_MSG_CLIENT_SNAP 130 
#define  CEPH_MSG_FS_MAP_USER 129 
#define  CEPH_MSG_MDS_MAP 128 
 scalar_t__ __verify_registered_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_handle_caps (struct ceph_mds_session*,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_handle_quota (struct ceph_mds_client*,struct ceph_mds_session*,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_handle_snap (struct ceph_mds_client*,struct ceph_mds_session*,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_mdsc_handle_fsmap (struct ceph_mds_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_mdsc_handle_mdsmap (struct ceph_mds_client*,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_type_name (int) ; 
 int /*<<< orphan*/  handle_forward (struct ceph_mds_client*,struct ceph_mds_session*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_lease (struct ceph_mds_client*,struct ceph_mds_session*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_reply (struct ceph_mds_session*,struct ceph_msg*) ; 
 int /*<<< orphan*/  handle_session (struct ceph_mds_session*,struct ceph_msg*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispatch(struct ceph_connection *con, struct ceph_msg *msg)
{
	struct ceph_mds_session *s = con->private;
	struct ceph_mds_client *mdsc = s->s_mdsc;
	int type = le16_to_cpu(msg->hdr.type);

	mutex_lock(&mdsc->mutex);
	if (__verify_registered_session(mdsc, s) < 0) {
		mutex_unlock(&mdsc->mutex);
		goto out;
	}
	mutex_unlock(&mdsc->mutex);

	switch (type) {
	case CEPH_MSG_MDS_MAP:
		ceph_mdsc_handle_mdsmap(mdsc, msg);
		break;
	case CEPH_MSG_FS_MAP_USER:
		ceph_mdsc_handle_fsmap(mdsc, msg);
		break;
	case CEPH_MSG_CLIENT_SESSION:
		handle_session(s, msg);
		break;
	case CEPH_MSG_CLIENT_REPLY:
		handle_reply(s, msg);
		break;
	case CEPH_MSG_CLIENT_REQUEST_FORWARD:
		handle_forward(mdsc, s, msg);
		break;
	case CEPH_MSG_CLIENT_CAPS:
		ceph_handle_caps(s, msg);
		break;
	case CEPH_MSG_CLIENT_SNAP:
		ceph_handle_snap(mdsc, s, msg);
		break;
	case CEPH_MSG_CLIENT_LEASE:
		handle_lease(mdsc, s, msg);
		break;
	case CEPH_MSG_CLIENT_QUOTA:
		ceph_handle_quota(mdsc, s, msg);
		break;

	default:
		pr_err("received unknown message type %d %s\n", type,
		       ceph_msg_type_name(type));
	}
out:
	ceph_msg_put(msg);
}