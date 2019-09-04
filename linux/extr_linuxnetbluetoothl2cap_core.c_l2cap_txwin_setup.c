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
struct l2cap_chan {scalar_t__ tx_win; scalar_t__ ack_win; scalar_t__ tx_win_max; int /*<<< orphan*/  flags; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_EXT_CTRL ; 
 scalar_t__ L2CAP_DEFAULT_EXT_WINDOW ; 
 scalar_t__ L2CAP_DEFAULT_TX_WINDOW ; 
 scalar_t__ __l2cap_ews_supported (int /*<<< orphan*/ ) ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static inline void l2cap_txwin_setup(struct l2cap_chan *chan)
{
	if (chan->tx_win > L2CAP_DEFAULT_TX_WINDOW &&
	    __l2cap_ews_supported(chan->conn)) {
		/* use extended control field */
		set_bit(FLAG_EXT_CTRL, &chan->flags);
		chan->tx_win_max = L2CAP_DEFAULT_EXT_WINDOW;
	} else {
		chan->tx_win = min_t(u16, chan->tx_win,
				     L2CAP_DEFAULT_TX_WINDOW);
		chan->tx_win_max = L2CAP_DEFAULT_TX_WINDOW;
	}
	chan->ack_win = chan->tx_win;
}