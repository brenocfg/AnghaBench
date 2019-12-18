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
struct l2cap_chan {scalar_t__ move_state; } ;

/* Variables and functions */
 scalar_t__ L2CAP_MOVE_STABLE ; 
 scalar_t__ L2CAP_MOVE_WAIT_PREPARE ; 

__attribute__((used)) static bool __chan_is_moving(struct l2cap_chan *chan)
{
	return chan->move_state != L2CAP_MOVE_STABLE &&
	       chan->move_state != L2CAP_MOVE_WAIT_PREPARE;
}