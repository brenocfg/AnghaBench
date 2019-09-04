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
typedef  int /*<<< orphan*/  u8 ;
struct l2cap_create_chan_req {int /*<<< orphan*/  amp_id; int /*<<< orphan*/  psm; int /*<<< orphan*/  scid; } ;
struct l2cap_chan {int /*<<< orphan*/  ident; int /*<<< orphan*/  conn; int /*<<< orphan*/  psm; int /*<<< orphan*/  scid; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_CREATE_CHAN_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_create_chan_req*) ; 

__attribute__((used)) static void l2cap_send_create_chan_req(struct l2cap_chan *chan, u8 amp_id)
{
	struct l2cap_create_chan_req req;
	req.scid = cpu_to_le16(chan->scid);
	req.psm  = chan->psm;
	req.amp_id = amp_id;

	chan->ident = l2cap_get_ident(chan->conn);

	l2cap_send_cmd(chan->conn, chan->ident, L2CAP_CREATE_CHAN_REQ,
		       sizeof(req), &req);
}