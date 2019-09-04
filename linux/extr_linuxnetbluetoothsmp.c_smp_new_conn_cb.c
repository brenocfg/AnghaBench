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
struct l2cap_chan {int /*<<< orphan*/  nesting; int /*<<< orphan*/  mode; int /*<<< orphan*/  omtu; int /*<<< orphan*/  imtu; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; int /*<<< orphan*/ * ops; int /*<<< orphan*/  chan_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  L2CAP_NESTING_SMP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct l2cap_chan* l2cap_chan_create () ; 
 int /*<<< orphan*/  smp_chan_ops ; 

__attribute__((used)) static inline struct l2cap_chan *smp_new_conn_cb(struct l2cap_chan *pchan)
{
	struct l2cap_chan *chan;

	BT_DBG("pchan %p", pchan);

	chan = l2cap_chan_create();
	if (!chan)
		return NULL;

	chan->chan_type	= pchan->chan_type;
	chan->ops	= &smp_chan_ops;
	chan->scid	= pchan->scid;
	chan->dcid	= chan->scid;
	chan->imtu	= pchan->imtu;
	chan->omtu	= pchan->omtu;
	chan->mode	= pchan->mode;

	/* Other L2CAP channels may request SMP routines in order to
	 * change the security level. This means that the SMP channel
	 * lock must be considered in its own category to avoid lockdep
	 * warnings.
	 */
	atomic_set(&chan->nesting, L2CAP_NESTING_SMP);

	BT_DBG("created chan %p", chan);

	return chan;
}