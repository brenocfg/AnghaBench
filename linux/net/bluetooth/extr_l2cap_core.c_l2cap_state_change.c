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
struct l2cap_chan {int state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* state_change ) (struct l2cap_chan*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_string (int) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_state_change(struct l2cap_chan *chan, int state)
{
	BT_DBG("chan %p %s -> %s", chan, state_to_string(chan->state),
	       state_to_string(state));

	chan->state = state;
	chan->ops->state_change(chan, state, 0);
}