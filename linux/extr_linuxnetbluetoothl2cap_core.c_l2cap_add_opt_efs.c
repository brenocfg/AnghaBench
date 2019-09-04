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
struct l2cap_conf_efs {int id; void* flush_to; void* acc_lat; void* sdu_itime; void* msdu; int /*<<< orphan*/  stype; } ;
struct l2cap_chan {int mode; int local_id; int /*<<< orphan*/  local_sdu_itime; int /*<<< orphan*/  local_msdu; int /*<<< orphan*/  local_stype; } ;
typedef  int /*<<< orphan*/  efs ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_CONF_EFS ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_ACC_LAT ; 
 int /*<<< orphan*/  L2CAP_EFS_DEFAULT_FLUSH_TO ; 
#define  L2CAP_MODE_ERTM 129 
#define  L2CAP_MODE_STREAMING 128 
 int /*<<< orphan*/  L2CAP_SERV_BESTEFFORT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_add_conf_opt (void**,int /*<<< orphan*/ ,int,unsigned long,size_t) ; 

__attribute__((used)) static void l2cap_add_opt_efs(void **ptr, struct l2cap_chan *chan, size_t size)
{
	struct l2cap_conf_efs efs;

	switch (chan->mode) {
	case L2CAP_MODE_ERTM:
		efs.id		= chan->local_id;
		efs.stype	= chan->local_stype;
		efs.msdu	= cpu_to_le16(chan->local_msdu);
		efs.sdu_itime	= cpu_to_le32(chan->local_sdu_itime);
		efs.acc_lat	= cpu_to_le32(L2CAP_DEFAULT_ACC_LAT);
		efs.flush_to	= cpu_to_le32(L2CAP_EFS_DEFAULT_FLUSH_TO);
		break;

	case L2CAP_MODE_STREAMING:
		efs.id		= 1;
		efs.stype	= L2CAP_SERV_BESTEFFORT;
		efs.msdu	= cpu_to_le16(chan->local_msdu);
		efs.sdu_itime	= cpu_to_le32(chan->local_sdu_itime);
		efs.acc_lat	= 0;
		efs.flush_to	= 0;
		break;

	default:
		return;
	}

	l2cap_add_conf_opt(ptr, L2CAP_CONF_EFS, sizeof(efs),
			   (unsigned long) &efs, size);
}