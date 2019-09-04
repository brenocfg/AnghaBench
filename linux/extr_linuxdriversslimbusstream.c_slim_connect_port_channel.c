#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct slim_val_inf {int member_1; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
struct slim_stream_runtime {struct slim_device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  id; } ;
struct slim_port {scalar_t__ direction; int /*<<< orphan*/  state; TYPE_1__ ch; int /*<<< orphan*/  id; } ;
struct slim_device {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  laddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SLIM_LDEST_TXN (TYPE_2__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct slim_val_inf*) ; 
 int /*<<< orphan*/  SLIM_CH_STATE_ASSOCIATED ; 
 int /*<<< orphan*/  SLIM_MSG_MC_CONNECT_SINK ; 
 int /*<<< orphan*/  SLIM_MSG_MC_CONNECT_SOURCE ; 
 scalar_t__ SLIM_PORT_SINK ; 
 int /*<<< orphan*/  SLIM_PORT_UNCONFIGURED ; 
 int slim_do_transfer (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__ txn ; 

__attribute__((used)) static int slim_connect_port_channel(struct slim_stream_runtime *stream,
				     struct slim_port *port)
{
	struct slim_device *sdev = stream->dev;
	u8 wbuf[2];
	struct slim_val_inf msg = {0, 2, NULL, wbuf, NULL};
	u8 mc = SLIM_MSG_MC_CONNECT_SOURCE;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 6, stream->dev->laddr, &msg);

	if (port->direction == SLIM_PORT_SINK)
		txn.mc = SLIM_MSG_MC_CONNECT_SINK;

	wbuf[0] = port->id;
	wbuf[1] = port->ch.id;
	port->ch.state = SLIM_CH_STATE_ASSOCIATED;
	port->state = SLIM_PORT_UNCONFIGURED;

	return slim_do_transfer(sdev->ctrl, &txn);
}