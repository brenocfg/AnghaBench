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
struct ncsi_package {unsigned char id; int /*<<< orphan*/  node; int /*<<< orphan*/  channel_whitelist; int /*<<< orphan*/  channels; int /*<<< orphan*/  lock; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  package_num; int /*<<< orphan*/  packages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  kfree (struct ncsi_package*) ; 
 struct ncsi_package* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ncsi_package* ncsi_find_package (struct ncsi_dev_priv*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ncsi_package *ncsi_add_package(struct ncsi_dev_priv *ndp,
				      unsigned char id)
{
	struct ncsi_package *np, *tmp;
	unsigned long flags;

	np = kzalloc(sizeof(*np), GFP_ATOMIC);
	if (!np)
		return NULL;

	np->id = id;
	np->ndp = ndp;
	spin_lock_init(&np->lock);
	INIT_LIST_HEAD(&np->channels);
	np->channel_whitelist = UINT_MAX;

	spin_lock_irqsave(&ndp->lock, flags);
	tmp = ncsi_find_package(ndp, id);
	if (tmp) {
		spin_unlock_irqrestore(&ndp->lock, flags);
		kfree(np);
		return tmp;
	}

	list_add_tail_rcu(&np->node, &ndp->packages);
	ndp->package_num++;
	spin_unlock_irqrestore(&ndp->lock, flags);

	return np;
}