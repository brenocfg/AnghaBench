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
struct l2cap_chan {scalar_t__ chan_type; int /*<<< orphan*/  conf_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_CONNECT_PEND ; 
 scalar_t__ L2CAP_CHAN_CONN_ORIENTED ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __l2cap_no_conn_pending(struct l2cap_chan *chan)
{
	if (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED)
		return true;

	return !test_bit(CONF_CONNECT_PEND, &chan->conf_state);
}