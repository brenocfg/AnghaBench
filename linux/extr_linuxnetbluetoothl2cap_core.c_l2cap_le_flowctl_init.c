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
struct l2cap_chan {int /*<<< orphan*/  tx_q; int /*<<< orphan*/  imtu; int /*<<< orphan*/  mps; int /*<<< orphan*/  rx_credits; scalar_t__ tx_credits; scalar_t__ sdu_len; int /*<<< orphan*/ * sdu_last_frag; int /*<<< orphan*/ * sdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  le_default_mps ; 
 int /*<<< orphan*/  le_max_credits ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static void l2cap_le_flowctl_init(struct l2cap_chan *chan)
{
	chan->sdu = NULL;
	chan->sdu_last_frag = NULL;
	chan->sdu_len = 0;
	chan->tx_credits = 0;
	chan->rx_credits = le_max_credits;
	chan->mps = min_t(u16, chan->imtu, le_default_mps);

	skb_queue_head_init(&chan->tx_q);
}