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
struct net_device {int /*<<< orphan*/  name; } ;
struct cflayer {int /*<<< orphan*/  transmit; int /*<<< orphan*/  name; } ;
struct cfcnfg {int dummy; } ;
struct caif_device_entry_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct caif_device_entry {struct cflayer layer; int /*<<< orphan*/  list; int /*<<< orphan*/  flow_lock; } ;
struct caif_dev_common {int link_select; int /*<<< orphan*/  use_fcs; } ;
typedef  enum cfcnfg_phy_preference { ____Placeholder_cfcnfg_phy_preference } cfcnfg_phy_preference ;

/* Variables and functions */
#define  CAIF_LINK_HIGH_BANDW 129 
#define  CAIF_LINK_LOW_LATENCY 128 
 int CFPHYPREF_HIGH_BW ; 
 int CFPHYPREF_LOW_LAT ; 
 struct caif_device_entry* caif_device_alloc (struct net_device*) ; 
 struct caif_device_entry_list* caif_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfcnfg_add_phy_layer (struct cfcnfg*,struct net_device*,struct cflayer*,int,struct cflayer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct cfcnfg* get_cfcnfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int receive (struct sk_buff*,struct net_device*,struct packet_type*,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  transmit ; 

void caif_enroll_dev(struct net_device *dev, struct caif_dev_common *caifdev,
		     struct cflayer *link_support, int head_room,
		     struct cflayer **layer,
		     int (**rcv_func)(struct sk_buff *, struct net_device *,
				      struct packet_type *,
				      struct net_device *))
{
	struct caif_device_entry *caifd;
	enum cfcnfg_phy_preference pref;
	struct cfcnfg *cfg = get_cfcnfg(dev_net(dev));
	struct caif_device_entry_list *caifdevs;

	caifdevs = caif_device_list(dev_net(dev));
	caifd = caif_device_alloc(dev);
	if (!caifd)
		return;
	*layer = &caifd->layer;
	spin_lock_init(&caifd->flow_lock);

	switch (caifdev->link_select) {
	case CAIF_LINK_HIGH_BANDW:
		pref = CFPHYPREF_HIGH_BW;
		break;
	case CAIF_LINK_LOW_LATENCY:
		pref = CFPHYPREF_LOW_LAT;
		break;
	default:
		pref = CFPHYPREF_HIGH_BW;
		break;
	}
	mutex_lock(&caifdevs->lock);
	list_add_rcu(&caifd->list, &caifdevs->list);

	strlcpy(caifd->layer.name, dev->name,
		sizeof(caifd->layer.name));
	caifd->layer.transmit = transmit;
	cfcnfg_add_phy_layer(cfg,
				dev,
				&caifd->layer,
				pref,
				link_support,
				caifdev->use_fcs,
				head_room);
	mutex_unlock(&caifdevs->lock);
	if (rcv_func)
		*rcv_func = receive;
}