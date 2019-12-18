#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ncsi_package {int /*<<< orphan*/  lock; int /*<<< orphan*/  channel_num; int /*<<< orphan*/  channels; } ;
struct TYPE_4__ {int enabled; int /*<<< orphan*/  timer; } ;
struct ncsi_channel {unsigned char id; int /*<<< orphan*/  node; TYPE_3__* modes; TYPE_2__* caps; int /*<<< orphan*/  link; int /*<<< orphan*/  lock; TYPE_1__ monitor; int /*<<< orphan*/  state; struct ncsi_package* package; } ;
struct TYPE_6__ {int index; } ;
struct TYPE_5__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NCSI_CAP_MAX ; 
 int /*<<< orphan*/  NCSI_CHANNEL_INACTIVE ; 
 int NCSI_MODE_MAX ; 
 int /*<<< orphan*/  kfree (struct ncsi_channel*) ; 
 struct ncsi_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncsi_channel_monitor ; 
 struct ncsi_channel* ncsi_find_channel (struct ncsi_package*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ncsi_channel *ncsi_add_channel(struct ncsi_package *np, unsigned char id)
{
	struct ncsi_channel *nc, *tmp;
	int index;
	unsigned long flags;

	nc = kzalloc(sizeof(*nc), GFP_ATOMIC);
	if (!nc)
		return NULL;

	nc->id = id;
	nc->package = np;
	nc->state = NCSI_CHANNEL_INACTIVE;
	nc->monitor.enabled = false;
	timer_setup(&nc->monitor.timer, ncsi_channel_monitor, 0);
	spin_lock_init(&nc->lock);
	INIT_LIST_HEAD(&nc->link);
	for (index = 0; index < NCSI_CAP_MAX; index++)
		nc->caps[index].index = index;
	for (index = 0; index < NCSI_MODE_MAX; index++)
		nc->modes[index].index = index;

	spin_lock_irqsave(&np->lock, flags);
	tmp = ncsi_find_channel(np, id);
	if (tmp) {
		spin_unlock_irqrestore(&np->lock, flags);
		kfree(nc);
		return tmp;
	}

	list_add_tail_rcu(&nc->node, &np->channels);
	np->channel_num++;
	spin_unlock_irqrestore(&np->lock, flags);

	return nc;
}