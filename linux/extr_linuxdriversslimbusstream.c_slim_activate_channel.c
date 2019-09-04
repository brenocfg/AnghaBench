#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct slim_val_inf {int member_1; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
struct slim_stream_runtime {struct slim_device* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; int /*<<< orphan*/  id; } ;
struct slim_port {TYPE_2__ ch; } ;
struct slim_device {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  laddr; } ;
struct TYPE_8__ {TYPE_1__* msg; } ;
struct TYPE_6__ {int num_bytes; int /*<<< orphan*/ * wbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SLIM_LDEST_TXN (TYPE_3__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct slim_val_inf*) ; 
 int /*<<< orphan*/  SLIM_CH_STATE_ACTIVE ; 
 int /*<<< orphan*/  SLIM_MSG_MC_NEXT_ACTIVATE_CHANNEL ; 
 int slim_do_transfer (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__ txn ; 

__attribute__((used)) static int slim_activate_channel(struct slim_stream_runtime *stream,
				 struct slim_port *port)
{
	struct slim_device *sdev = stream->dev;
	u8 wbuf[1];
	struct slim_val_inf msg = {0, 1, NULL, wbuf, NULL};
	u8 mc = SLIM_MSG_MC_NEXT_ACTIVATE_CHANNEL;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 5, stream->dev->laddr, &msg);

	txn.msg->num_bytes = 1;
	txn.msg->wbuf = wbuf;
	wbuf[0] = port->ch.id;
	port->ch.state = SLIM_CH_STATE_ACTIVE;

	return slim_do_transfer(sdev->ctrl, &txn);
}