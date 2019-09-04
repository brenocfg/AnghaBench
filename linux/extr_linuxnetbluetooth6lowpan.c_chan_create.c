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
struct l2cap_chan {int imtu; int /*<<< orphan*/  mode; int /*<<< orphan*/  chan_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_CHAN_CONN_ORIENTED ; 
 int /*<<< orphan*/  L2CAP_MODE_LE_FLOWCTL ; 
 struct l2cap_chan* l2cap_chan_create () ; 
 int /*<<< orphan*/  l2cap_chan_set_defaults (struct l2cap_chan*) ; 

__attribute__((used)) static struct l2cap_chan *chan_create(void)
{
	struct l2cap_chan *chan;

	chan = l2cap_chan_create();
	if (!chan)
		return NULL;

	l2cap_chan_set_defaults(chan);

	chan->chan_type = L2CAP_CHAN_CONN_ORIENTED;
	chan->mode = L2CAP_MODE_LE_FLOWCTL;
	chan->imtu = 1280;

	return chan;
}