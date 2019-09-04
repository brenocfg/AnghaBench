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
struct l2cap_chan {int /*<<< orphan*/  state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* state_change ) (struct l2cap_chan*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct l2cap_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void l2cap_chan_set_err(struct l2cap_chan *chan, int err)
{
	chan->ops->state_change(chan, chan->state, err);
}