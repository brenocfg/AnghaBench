#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; int /*<<< orphan*/  ifindex; } ;
struct cflayer {int dummy; } ;
struct cfcnfg {int dummy; } ;
struct caif_device_entry_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; TYPE_2__* up; } ;
struct caif_device_entry {int /*<<< orphan*/  pcpu_refcnt; int /*<<< orphan*/  netdev; int /*<<< orphan*/  list; TYPE_3__ layer; int /*<<< orphan*/  flow_lock; TYPE_1__* xoff_skb; int /*<<< orphan*/ * xoff_skb_dtor; int /*<<< orphan*/  xoff; } ;
struct caif_dev_common {int /*<<< orphan*/  flowctrl; int /*<<< orphan*/  use_stx; int /*<<< orphan*/  use_frag; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * destructor; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAIF ; 
 int EINVAL ; 
#define  NETDEV_DOWN 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  _CAIF_CTRLCMD_PHYIF_DOWN_IND ; 
 struct caif_device_entry_list* caif_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caif_enroll_dev (struct net_device*,struct caif_dev_common*,struct cflayer*,int,struct cflayer**,int /*<<< orphan*/ *) ; 
 struct caif_device_entry* caif_get (struct net_device*) ; 
 int /*<<< orphan*/  caifd_hold (struct caif_device_entry*) ; 
 int /*<<< orphan*/  caifd_put (struct caif_device_entry*) ; 
 int /*<<< orphan*/  caifd_refcnt_read (struct caif_device_entry*) ; 
 int /*<<< orphan*/  cfcnfg_del_phy_layer (struct cfcnfg*,TYPE_3__*) ; 
 int /*<<< orphan*/  cfcnfg_set_phy_state (struct cfcnfg*,TYPE_3__*,int) ; 
 struct cflayer* cfserl_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_flowctrl ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct cfcnfg* get_cfcnfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct caif_device_entry*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct caif_dev_common* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int caif_device_notify(struct notifier_block *me, unsigned long what,
			      void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct caif_device_entry *caifd = NULL;
	struct caif_dev_common *caifdev;
	struct cfcnfg *cfg;
	struct cflayer *layer, *link_support;
	int head_room = 0;
	struct caif_device_entry_list *caifdevs;

	cfg = get_cfcnfg(dev_net(dev));
	caifdevs = caif_device_list(dev_net(dev));

	caifd = caif_get(dev);
	if (caifd == NULL && dev->type != ARPHRD_CAIF)
		return 0;

	switch (what) {
	case NETDEV_REGISTER:
		if (caifd != NULL)
			break;

		caifdev = netdev_priv(dev);

		link_support = NULL;
		if (caifdev->use_frag) {
			head_room = 1;
			link_support = cfserl_create(dev->ifindex,
							caifdev->use_stx);
			if (!link_support) {
				pr_warn("Out of memory\n");
				break;
			}
		}
		caif_enroll_dev(dev, caifdev, link_support, head_room,
				&layer, NULL);
		caifdev->flowctrl = dev_flowctrl;
		break;

	case NETDEV_UP:
		rcu_read_lock();

		caifd = caif_get(dev);
		if (caifd == NULL) {
			rcu_read_unlock();
			break;
		}

		caifd->xoff = 0;
		cfcnfg_set_phy_state(cfg, &caifd->layer, true);
		rcu_read_unlock();

		break;

	case NETDEV_DOWN:
		rcu_read_lock();

		caifd = caif_get(dev);
		if (!caifd || !caifd->layer.up || !caifd->layer.up->ctrlcmd) {
			rcu_read_unlock();
			return -EINVAL;
		}

		cfcnfg_set_phy_state(cfg, &caifd->layer, false);
		caifd_hold(caifd);
		rcu_read_unlock();

		caifd->layer.up->ctrlcmd(caifd->layer.up,
					 _CAIF_CTRLCMD_PHYIF_DOWN_IND,
					 caifd->layer.id);

		spin_lock_bh(&caifd->flow_lock);

		/*
		 * Replace our xoff-destructor with original destructor.
		 * We trust that skb->destructor *always* is called before
		 * the skb reference is invalid. The hijacked SKB destructor
		 * takes the flow_lock so manipulating the skb->destructor here
		 * should be safe.
		*/
		if (caifd->xoff_skb_dtor != NULL && caifd->xoff_skb != NULL)
			caifd->xoff_skb->destructor = caifd->xoff_skb_dtor;

		caifd->xoff = 0;
		caifd->xoff_skb_dtor = NULL;
		caifd->xoff_skb = NULL;

		spin_unlock_bh(&caifd->flow_lock);
		caifd_put(caifd);
		break;

	case NETDEV_UNREGISTER:
		mutex_lock(&caifdevs->lock);

		caifd = caif_get(dev);
		if (caifd == NULL) {
			mutex_unlock(&caifdevs->lock);
			break;
		}
		list_del_rcu(&caifd->list);

		/*
		 * NETDEV_UNREGISTER is called repeatedly until all reference
		 * counts for the net-device are released. If references to
		 * caifd is taken, simply ignore NETDEV_UNREGISTER and wait for
		 * the next call to NETDEV_UNREGISTER.
		 *
		 * If any packets are in flight down the CAIF Stack,
		 * cfcnfg_del_phy_layer will return nonzero.
		 * If no packets are in flight, the CAIF Stack associated
		 * with the net-device un-registering is freed.
		 */

		if (caifd_refcnt_read(caifd) != 0 ||
			cfcnfg_del_phy_layer(cfg, &caifd->layer) != 0) {

			pr_info("Wait for device inuse\n");
			/* Enrole device if CAIF Stack is still in use */
			list_add_rcu(&caifd->list, &caifdevs->list);
			mutex_unlock(&caifdevs->lock);
			break;
		}

		synchronize_rcu();
		dev_put(caifd->netdev);
		free_percpu(caifd->pcpu_refcnt);
		kfree(caifd);

		mutex_unlock(&caifdevs->lock);
		break;
	}
	return 0;
}