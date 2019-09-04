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
typedef  int u32 ;
struct switchtec_ntb {int peer_partition; TYPE_1__* mmio_self_dbmsg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * imsg; int /*<<< orphan*/  msg_map; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int NTB_DBMSG_IMSG_MASK ; 
 int NTB_DBMSG_IMSG_STATUS ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite64 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void switchtec_ntb_init_msgs(struct switchtec_ntb *sndev)
{
	int i;
	u32 msg_map = 0;

	for (i = 0; i < ARRAY_SIZE(sndev->mmio_self_dbmsg->imsg); i++) {
		int m = i | sndev->peer_partition << 2;

		msg_map |= m << i * 8;
	}

	iowrite32(msg_map, &sndev->mmio_self_dbmsg->msg_map);

	for (i = 0; i < ARRAY_SIZE(sndev->mmio_self_dbmsg->imsg); i++)
		iowrite64(NTB_DBMSG_IMSG_STATUS | NTB_DBMSG_IMSG_MASK,
			  &sndev->mmio_self_dbmsg->imsg[i]);
}