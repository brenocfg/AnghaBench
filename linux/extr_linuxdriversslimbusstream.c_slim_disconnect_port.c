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
typedef  int /*<<< orphan*/  u8 ;
struct slim_val_inf {int member_1; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
struct slim_stream_runtime {struct slim_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct slim_port {int /*<<< orphan*/  state; TYPE_1__ ch; int /*<<< orphan*/  id; } ;
struct slim_device {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SLIM_LDEST_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct slim_val_inf*) ; 
 int /*<<< orphan*/  SLIM_CH_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  SLIM_MSG_MC_DISCONNECT_PORT ; 
 int /*<<< orphan*/  SLIM_PORT_DISCONNECTED ; 
 int slim_do_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn ; 

__attribute__((used)) static int slim_disconnect_port(struct slim_stream_runtime *stream,
				struct slim_port *port)
{
	struct slim_device *sdev = stream->dev;
	u8 wbuf[1];
	struct slim_val_inf msg = {0, 1, NULL, wbuf, NULL};
	u8 mc = SLIM_MSG_MC_DISCONNECT_PORT;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 5, stream->dev->laddr, &msg);

	wbuf[0] = port->id;
	port->ch.state = SLIM_CH_STATE_DISCONNECTED;
	port->state = SLIM_PORT_DISCONNECTED;

	return slim_do_transfer(sdev->ctrl, &txn);
}