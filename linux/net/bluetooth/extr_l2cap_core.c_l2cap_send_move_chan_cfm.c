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
typedef  int /*<<< orphan*/  u16 ;
struct l2cap_move_chan_cfm {void* result; void* icid; } ;
struct l2cap_chan {int /*<<< orphan*/  ident; int /*<<< orphan*/  conn; int /*<<< orphan*/  scid; } ;
typedef  int /*<<< orphan*/  cfm ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_MOVE_CHAN_CFM ; 
 int /*<<< orphan*/  L2CAP_MOVE_TIMEOUT ; 
 int /*<<< orphan*/  __set_chan_timer (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_move_chan_cfm*) ; 

__attribute__((used)) static void l2cap_send_move_chan_cfm(struct l2cap_chan *chan, u16 result)
{
	struct l2cap_move_chan_cfm cfm;

	BT_DBG("chan %p, result 0x%4.4x", chan, result);

	chan->ident = l2cap_get_ident(chan->conn);

	cfm.icid = cpu_to_le16(chan->scid);
	cfm.result = cpu_to_le16(result);

	l2cap_send_cmd(chan->conn, chan->ident, L2CAP_MOVE_CHAN_CFM,
		       sizeof(cfm), &cfm);

	__set_chan_timer(chan, L2CAP_MOVE_TIMEOUT);
}