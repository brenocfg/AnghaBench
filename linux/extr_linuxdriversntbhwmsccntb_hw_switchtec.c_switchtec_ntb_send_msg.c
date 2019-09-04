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
typedef  int /*<<< orphan*/  u32 ;
struct switchtec_ntb {TYPE_1__* mmio_peer_dbmsg; } ;
struct TYPE_4__ {int /*<<< orphan*/  msg; } ;
struct TYPE_3__ {TYPE_2__* omsg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int switchtec_ntb_send_msg(struct switchtec_ntb *sndev, int idx,
				  u32 val)
{
	if (idx < 0 || idx >= ARRAY_SIZE(sndev->mmio_peer_dbmsg->omsg))
		return -EINVAL;

	iowrite32(val, &sndev->mmio_peer_dbmsg->omsg[idx].msg);

	return 0;
}