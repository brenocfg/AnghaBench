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
#define  CEPH_OSD_WATCH_OP_PING 131 
#define  CEPH_OSD_WATCH_OP_RECONNECT 130 
#define  CEPH_OSD_WATCH_OP_UNWATCH 129 
#define  CEPH_OSD_WATCH_OP_WATCH 128 

const char *ceph_osd_watch_op_name(int o)
{
	switch (o) {
	case CEPH_OSD_WATCH_OP_UNWATCH:
		return "unwatch";
	case CEPH_OSD_WATCH_OP_WATCH:
		return "watch";
	case CEPH_OSD_WATCH_OP_RECONNECT:
		return "reconnect";
	case CEPH_OSD_WATCH_OP_PING:
		return "ping";
	default:
		return "???";
	}
}