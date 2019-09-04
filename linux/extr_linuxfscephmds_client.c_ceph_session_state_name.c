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
#define  CEPH_MDS_SESSION_CLOSING 135 
#define  CEPH_MDS_SESSION_HUNG 134 
#define  CEPH_MDS_SESSION_NEW 133 
#define  CEPH_MDS_SESSION_OPEN 132 
#define  CEPH_MDS_SESSION_OPENING 131 
#define  CEPH_MDS_SESSION_RECONNECTING 130 
#define  CEPH_MDS_SESSION_REJECTED 129 
#define  CEPH_MDS_SESSION_RESTARTING 128 

const char *ceph_session_state_name(int s)
{
	switch (s) {
	case CEPH_MDS_SESSION_NEW: return "new";
	case CEPH_MDS_SESSION_OPENING: return "opening";
	case CEPH_MDS_SESSION_OPEN: return "open";
	case CEPH_MDS_SESSION_HUNG: return "hung";
	case CEPH_MDS_SESSION_CLOSING: return "closing";
	case CEPH_MDS_SESSION_RESTARTING: return "restarting";
	case CEPH_MDS_SESSION_RECONNECTING: return "reconnecting";
	case CEPH_MDS_SESSION_REJECTED: return "rejected";
	default: return "???";
	}
}