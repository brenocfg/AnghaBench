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

/* Variables and functions */
#define  CEPH_MSG_AUTH 160 
#define  CEPH_MSG_AUTH_REPLY 159 
#define  CEPH_MSG_CLIENT_CAPRELEASE 158 
#define  CEPH_MSG_CLIENT_CAPS 157 
#define  CEPH_MSG_CLIENT_LEASE 156 
#define  CEPH_MSG_CLIENT_QUOTA 155 
#define  CEPH_MSG_CLIENT_RECONNECT 154 
#define  CEPH_MSG_CLIENT_REPLY 153 
#define  CEPH_MSG_CLIENT_REQUEST 152 
#define  CEPH_MSG_CLIENT_REQUEST_FORWARD 151 
#define  CEPH_MSG_CLIENT_SESSION 150 
#define  CEPH_MSG_CLIENT_SNAP 149 
#define  CEPH_MSG_FS_MAP_USER 148 
#define  CEPH_MSG_MDS_MAP 147 
#define  CEPH_MSG_MON_COMMAND 146 
#define  CEPH_MSG_MON_COMMAND_ACK 145 
#define  CEPH_MSG_MON_GET_MAP 144 
#define  CEPH_MSG_MON_GET_VERSION 143 
#define  CEPH_MSG_MON_GET_VERSION_REPLY 142 
#define  CEPH_MSG_MON_MAP 141 
#define  CEPH_MSG_MON_SUBSCRIBE 140 
#define  CEPH_MSG_MON_SUBSCRIBE_ACK 139 
#define  CEPH_MSG_OSD_BACKOFF 138 
#define  CEPH_MSG_OSD_MAP 137 
#define  CEPH_MSG_OSD_OP 136 
#define  CEPH_MSG_OSD_OPREPLY 135 
#define  CEPH_MSG_PING 134 
#define  CEPH_MSG_POOLOP 133 
#define  CEPH_MSG_POOLOP_REPLY 132 
#define  CEPH_MSG_SHUTDOWN 131 
#define  CEPH_MSG_STATFS 130 
#define  CEPH_MSG_STATFS_REPLY 129 
#define  CEPH_MSG_WATCH_NOTIFY 128 

const char *ceph_msg_type_name(int type)
{
	switch (type) {
	case CEPH_MSG_SHUTDOWN: return "shutdown";
	case CEPH_MSG_PING: return "ping";
	case CEPH_MSG_AUTH: return "auth";
	case CEPH_MSG_AUTH_REPLY: return "auth_reply";
	case CEPH_MSG_MON_MAP: return "mon_map";
	case CEPH_MSG_MON_GET_MAP: return "mon_get_map";
	case CEPH_MSG_MON_SUBSCRIBE: return "mon_subscribe";
	case CEPH_MSG_MON_SUBSCRIBE_ACK: return "mon_subscribe_ack";
	case CEPH_MSG_STATFS: return "statfs";
	case CEPH_MSG_STATFS_REPLY: return "statfs_reply";
	case CEPH_MSG_MON_GET_VERSION: return "mon_get_version";
	case CEPH_MSG_MON_GET_VERSION_REPLY: return "mon_get_version_reply";
	case CEPH_MSG_MDS_MAP: return "mds_map";
	case CEPH_MSG_FS_MAP_USER: return "fs_map_user";
	case CEPH_MSG_CLIENT_SESSION: return "client_session";
	case CEPH_MSG_CLIENT_RECONNECT: return "client_reconnect";
	case CEPH_MSG_CLIENT_REQUEST: return "client_request";
	case CEPH_MSG_CLIENT_REQUEST_FORWARD: return "client_request_forward";
	case CEPH_MSG_CLIENT_REPLY: return "client_reply";
	case CEPH_MSG_CLIENT_CAPS: return "client_caps";
	case CEPH_MSG_CLIENT_CAPRELEASE: return "client_cap_release";
	case CEPH_MSG_CLIENT_QUOTA: return "client_quota";
	case CEPH_MSG_CLIENT_SNAP: return "client_snap";
	case CEPH_MSG_CLIENT_LEASE: return "client_lease";
	case CEPH_MSG_POOLOP_REPLY: return "poolop_reply";
	case CEPH_MSG_POOLOP: return "poolop";
	case CEPH_MSG_MON_COMMAND: return "mon_command";
	case CEPH_MSG_MON_COMMAND_ACK: return "mon_command_ack";
	case CEPH_MSG_OSD_MAP: return "osd_map";
	case CEPH_MSG_OSD_OP: return "osd_op";
	case CEPH_MSG_OSD_OPREPLY: return "osd_opreply";
	case CEPH_MSG_WATCH_NOTIFY: return "watch_notify";
	case CEPH_MSG_OSD_BACKOFF: return "osd_backoff";
	default: return "unknown";
	}
}