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
struct l2cap_chan {int /*<<< orphan*/  conf_state; int /*<<< orphan*/  kref; int /*<<< orphan*/  state; int /*<<< orphan*/  chan_timer; int /*<<< orphan*/  global_l; int /*<<< orphan*/  nesting; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  CONF_NOT_COMPLETE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_NESTING_NORMAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_list ; 
 int /*<<< orphan*/  chan_list_lock ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct l2cap_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_timeout ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct l2cap_chan *l2cap_chan_create(void)
{
	struct l2cap_chan *chan;

	chan = kzalloc(sizeof(*chan), GFP_ATOMIC);
	if (!chan)
		return NULL;

	mutex_init(&chan->lock);

	/* Set default lock nesting level */
	atomic_set(&chan->nesting, L2CAP_NESTING_NORMAL);

	write_lock(&chan_list_lock);
	list_add(&chan->global_l, &chan_list);
	write_unlock(&chan_list_lock);

	INIT_DELAYED_WORK(&chan->chan_timer, l2cap_chan_timeout);

	chan->state = BT_OPEN;

	kref_init(&chan->kref);

	/* This flag is cleared in l2cap_chan_ready() */
	set_bit(CONF_NOT_COMPLETE, &chan->conf_state);

	BT_DBG("chan %p", chan);

	return chan;
}