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
#define  CEPH_SESSION_CLOSE 139 
#define  CEPH_SESSION_FLUSHMSG 138 
#define  CEPH_SESSION_FLUSHMSG_ACK 137 
#define  CEPH_SESSION_FORCE_RO 136 
#define  CEPH_SESSION_OPEN 135 
#define  CEPH_SESSION_RECALL_STATE 134 
#define  CEPH_SESSION_REJECT 133 
#define  CEPH_SESSION_RENEWCAPS 132 
#define  CEPH_SESSION_REQUEST_CLOSE 131 
#define  CEPH_SESSION_REQUEST_OPEN 130 
#define  CEPH_SESSION_REQUEST_RENEWCAPS 129 
#define  CEPH_SESSION_STALE 128 

const char *ceph_session_op_name(int op)
{
	switch (op) {
	case CEPH_SESSION_REQUEST_OPEN: return "request_open";
	case CEPH_SESSION_OPEN: return "open";
	case CEPH_SESSION_REQUEST_CLOSE: return "request_close";
	case CEPH_SESSION_CLOSE: return "close";
	case CEPH_SESSION_REQUEST_RENEWCAPS: return "request_renewcaps";
	case CEPH_SESSION_RENEWCAPS: return "renewcaps";
	case CEPH_SESSION_STALE: return "stale";
	case CEPH_SESSION_RECALL_STATE: return "recall_state";
	case CEPH_SESSION_FLUSHMSG: return "flushmsg";
	case CEPH_SESSION_FLUSHMSG_ACK: return "flushmsg_ack";
	case CEPH_SESSION_FORCE_RO: return "force_ro";
	case CEPH_SESSION_REJECT: return "reject";
	}
	return "???";
}