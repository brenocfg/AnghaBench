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
struct l2cap_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 

__attribute__((used)) static void a2mp_chan_close_cb(struct l2cap_chan *chan)
{
	l2cap_chan_put(chan);
}