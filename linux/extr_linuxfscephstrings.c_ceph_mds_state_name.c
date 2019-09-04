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
#define  CEPH_MDS_STATE_ACTIVE 142 
#define  CEPH_MDS_STATE_BOOT 141 
#define  CEPH_MDS_STATE_CLIENTREPLAY 140 
#define  CEPH_MDS_STATE_CREATING 139 
#define  CEPH_MDS_STATE_DNE 138 
#define  CEPH_MDS_STATE_RECONNECT 137 
#define  CEPH_MDS_STATE_REJOIN 136 
#define  CEPH_MDS_STATE_REPLAY 135 
#define  CEPH_MDS_STATE_REPLAYONCE 134 
#define  CEPH_MDS_STATE_RESOLVE 133 
#define  CEPH_MDS_STATE_STANDBY 132 
#define  CEPH_MDS_STATE_STANDBY_REPLAY 131 
#define  CEPH_MDS_STATE_STARTING 130 
#define  CEPH_MDS_STATE_STOPPED 129 
#define  CEPH_MDS_STATE_STOPPING 128 

const char *ceph_mds_state_name(int s)
{
	switch (s) {
		/* down and out */
	case CEPH_MDS_STATE_DNE:        return "down:dne";
	case CEPH_MDS_STATE_STOPPED:    return "down:stopped";
		/* up and out */
	case CEPH_MDS_STATE_BOOT:       return "up:boot";
	case CEPH_MDS_STATE_STANDBY:    return "up:standby";
	case CEPH_MDS_STATE_STANDBY_REPLAY:    return "up:standby-replay";
	case CEPH_MDS_STATE_REPLAYONCE: return "up:oneshot-replay";
	case CEPH_MDS_STATE_CREATING:   return "up:creating";
	case CEPH_MDS_STATE_STARTING:   return "up:starting";
		/* up and in */
	case CEPH_MDS_STATE_REPLAY:     return "up:replay";
	case CEPH_MDS_STATE_RESOLVE:    return "up:resolve";
	case CEPH_MDS_STATE_RECONNECT:  return "up:reconnect";
	case CEPH_MDS_STATE_REJOIN:     return "up:rejoin";
	case CEPH_MDS_STATE_CLIENTREPLAY: return "up:clientreplay";
	case CEPH_MDS_STATE_ACTIVE:     return "up:active";
	case CEPH_MDS_STATE_STOPPING:   return "up:stopping";
	}
	return "???";
}