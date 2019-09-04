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
struct l2cap_chan {int /*<<< orphan*/  scid; int /*<<< orphan*/  chan_type; int /*<<< orphan*/  omtu; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_CHAN_FIXED ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MTU ; 
 int /*<<< orphan*/  chan_list_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int l2cap_add_scid(struct l2cap_chan *chan,  __u16 scid)
{
	write_lock(&chan_list_lock);

	/* Override the defaults (which are for conn-oriented) */
	chan->omtu = L2CAP_DEFAULT_MTU;
	chan->chan_type = L2CAP_CHAN_FIXED;

	chan->scid = scid;

	write_unlock(&chan_list_lock);

	return 0;
}