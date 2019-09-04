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
struct ceph_msg_header {int /*<<< orphan*/  tid; int /*<<< orphan*/  front_len; int /*<<< orphan*/  type; } ;
struct ceph_msg {int front_alloc_len; } ;
struct ceph_mon_client {int /*<<< orphan*/  m_auth_reply; int /*<<< orphan*/  m_subscribe_ack; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; scalar_t__ type; } ;
struct ceph_connection {TYPE_1__ peer_name; struct ceph_mon_client* private; } ;

/* Variables and functions */
#define  CEPH_MSG_AUTH_REPLY 136 
#define  CEPH_MSG_FS_MAP_USER 135 
#define  CEPH_MSG_MDS_MAP 134 
#define  CEPH_MSG_MON_COMMAND_ACK 133 
#define  CEPH_MSG_MON_GET_VERSION_REPLY 132 
#define  CEPH_MSG_MON_MAP 131 
#define  CEPH_MSG_MON_SUBSCRIBE_ACK 130 
#define  CEPH_MSG_OSD_MAP 129 
#define  CEPH_MSG_STATFS_REPLY 128 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct ceph_msg* ceph_msg_get (int /*<<< orphan*/ ) ; 
 struct ceph_msg* ceph_msg_new (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 struct ceph_msg* get_generic_reply (struct ceph_connection*,struct ceph_msg_header*,int*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_msg *mon_alloc_msg(struct ceph_connection *con,
				      struct ceph_msg_header *hdr,
				      int *skip)
{
	struct ceph_mon_client *monc = con->private;
	int type = le16_to_cpu(hdr->type);
	int front_len = le32_to_cpu(hdr->front_len);
	struct ceph_msg *m = NULL;

	*skip = 0;

	switch (type) {
	case CEPH_MSG_MON_SUBSCRIBE_ACK:
		m = ceph_msg_get(monc->m_subscribe_ack);
		break;
	case CEPH_MSG_STATFS_REPLY:
	case CEPH_MSG_MON_COMMAND_ACK:
		return get_generic_reply(con, hdr, skip);
	case CEPH_MSG_AUTH_REPLY:
		m = ceph_msg_get(monc->m_auth_reply);
		break;
	case CEPH_MSG_MON_GET_VERSION_REPLY:
		if (le64_to_cpu(hdr->tid) != 0)
			return get_generic_reply(con, hdr, skip);

		/*
		 * Older OSDs don't set reply tid even if the orignal
		 * request had a non-zero tid.  Work around this weirdness
		 * by allocating a new message.
		 */
		/* fall through */
	case CEPH_MSG_MON_MAP:
	case CEPH_MSG_MDS_MAP:
	case CEPH_MSG_OSD_MAP:
	case CEPH_MSG_FS_MAP_USER:
		m = ceph_msg_new(type, front_len, GFP_NOFS, false);
		if (!m)
			return NULL;	/* ENOMEM--return skip == 0 */
		break;
	}

	if (!m) {
		pr_info("alloc_msg unknown type %d\n", type);
		*skip = 1;
	} else if (front_len > m->front_alloc_len) {
		pr_warn("mon_alloc_msg front %d > prealloc %d (%u#%llu)\n",
			front_len, m->front_alloc_len,
			(unsigned int)con->peer_name.type,
			le64_to_cpu(con->peer_name.num));
		ceph_msg_put(m);
		m = ceph_msg_new(type, front_len, GFP_NOFS, false);
	}

	return m;
}