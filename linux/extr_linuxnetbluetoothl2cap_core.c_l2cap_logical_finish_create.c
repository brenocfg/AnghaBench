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
struct l2cap_conf_rsp {int dummy; } ;
struct l2cap_chan {int /*<<< orphan*/  conf_state; int /*<<< orphan*/  ident; int /*<<< orphan*/  conn; TYPE_1__* hs_hcon; struct hci_chan* hs_hchan; } ;
struct hci_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  l2cap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_INPUT_DONE ; 
 int /*<<< orphan*/  l2cap_chan_ready (struct l2cap_chan*) ; 
 int l2cap_ertm_init (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  l2cap_send_efs_conf_rsp (struct l2cap_chan*,struct l2cap_conf_rsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_fcs (struct l2cap_chan*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_logical_finish_create(struct l2cap_chan *chan,
					struct hci_chan *hchan)
{
	struct l2cap_conf_rsp rsp;

	chan->hs_hchan = hchan;
	chan->hs_hcon->l2cap_data = chan->conn;

	l2cap_send_efs_conf_rsp(chan, &rsp, chan->ident, 0);

	if (test_bit(CONF_INPUT_DONE, &chan->conf_state)) {
		int err;

		set_default_fcs(chan);

		err = l2cap_ertm_init(chan);
		if (err < 0)
			l2cap_send_disconn_req(chan, -err);
		else
			l2cap_chan_ready(chan);
	}
}