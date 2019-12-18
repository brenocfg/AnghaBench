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
struct l2cap_chan {int /*<<< orphan*/  flags; scalar_t__ conf_state; int /*<<< orphan*/  monitor_timeout; int /*<<< orphan*/  retrans_timeout; int /*<<< orphan*/  flush_to; int /*<<< orphan*/  sec_level; void* ack_win; void* tx_win; void* remote_tx_win; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  remote_max_tx; void* tx_win_max; int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int /*<<< orphan*/  FLAG_FORCE_ACTIVE ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_FLUSH_TO ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MAX_TX ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MONITOR_TO ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_RETRANS_TO ; 
 void* L2CAP_DEFAULT_TX_WINDOW ; 
 int /*<<< orphan*/  L2CAP_FCS_CRC16 ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void l2cap_chan_set_defaults(struct l2cap_chan *chan)
{
	chan->fcs  = L2CAP_FCS_CRC16;
	chan->max_tx = L2CAP_DEFAULT_MAX_TX;
	chan->tx_win = L2CAP_DEFAULT_TX_WINDOW;
	chan->tx_win_max = L2CAP_DEFAULT_TX_WINDOW;
	chan->remote_max_tx = chan->max_tx;
	chan->remote_tx_win = chan->tx_win;
	chan->ack_win = L2CAP_DEFAULT_TX_WINDOW;
	chan->sec_level = BT_SECURITY_LOW;
	chan->flush_to = L2CAP_DEFAULT_FLUSH_TO;
	chan->retrans_timeout = L2CAP_DEFAULT_RETRANS_TO;
	chan->monitor_timeout = L2CAP_DEFAULT_MONITOR_TO;
	chan->conf_state = 0;

	set_bit(FLAG_FORCE_ACTIVE, &chan->flags);
}