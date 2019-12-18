#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int flags; TYPE_1__* header_ops; int /*<<< orphan*/  addr_len; int /*<<< orphan*/ * broadcast; int /*<<< orphan*/ * dev_addr; } ;
struct neighbour {int nud_state; TYPE_3__* ops; int /*<<< orphan*/  output; scalar_t__ ha; int /*<<< orphan*/  type; int /*<<< orphan*/  parms; scalar_t__ primary_key; struct net_device* dev; } ;
struct neigh_parms {int dummy; } ;
struct in_device {struct neigh_parms* arp_parms; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {int /*<<< orphan*/  output; int /*<<< orphan*/  connected_output; } ;
struct TYPE_7__ {int /*<<< orphan*/  key_len; } ;
struct TYPE_6__ {scalar_t__ cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 void* NUD_NOARP ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  RTN_BROADCAST ; 
 int /*<<< orphan*/  RTN_MULTICAST ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  __neigh_parms_put (int /*<<< orphan*/ ) ; 
 TYPE_3__ arp_direct_ops ; 
 TYPE_3__ arp_generic_ops ; 
 TYPE_3__ arp_hh_ops ; 
 int /*<<< orphan*/  arp_mc_map (int /*<<< orphan*/ ,scalar_t__,struct net_device*,int) ; 
 TYPE_2__ arp_tbl ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  inet_addr_type_dev_table (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_direct_output ; 
 int /*<<< orphan*/  neigh_parms_clone (struct neigh_parms*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int arp_constructor(struct neighbour *neigh)
{
	__be32 addr;
	struct net_device *dev = neigh->dev;
	struct in_device *in_dev;
	struct neigh_parms *parms;
	u32 inaddr_any = INADDR_ANY;

	if (dev->flags & (IFF_LOOPBACK | IFF_POINTOPOINT))
		memcpy(neigh->primary_key, &inaddr_any, arp_tbl.key_len);

	addr = *(__be32 *)neigh->primary_key;
	rcu_read_lock();
	in_dev = __in_dev_get_rcu(dev);
	if (!in_dev) {
		rcu_read_unlock();
		return -EINVAL;
	}

	neigh->type = inet_addr_type_dev_table(dev_net(dev), dev, addr);

	parms = in_dev->arp_parms;
	__neigh_parms_put(neigh->parms);
	neigh->parms = neigh_parms_clone(parms);
	rcu_read_unlock();

	if (!dev->header_ops) {
		neigh->nud_state = NUD_NOARP;
		neigh->ops = &arp_direct_ops;
		neigh->output = neigh_direct_output;
	} else {
		/* Good devices (checked by reading texts, but only Ethernet is
		   tested)

		   ARPHRD_ETHER: (ethernet, apfddi)
		   ARPHRD_FDDI: (fddi)
		   ARPHRD_IEEE802: (tr)
		   ARPHRD_METRICOM: (strip)
		   ARPHRD_ARCNET:
		   etc. etc. etc.

		   ARPHRD_IPDDP will also work, if author repairs it.
		   I did not it, because this driver does not work even
		   in old paradigm.
		 */

		if (neigh->type == RTN_MULTICAST) {
			neigh->nud_state = NUD_NOARP;
			arp_mc_map(addr, neigh->ha, dev, 1);
		} else if (dev->flags & (IFF_NOARP | IFF_LOOPBACK)) {
			neigh->nud_state = NUD_NOARP;
			memcpy(neigh->ha, dev->dev_addr, dev->addr_len);
		} else if (neigh->type == RTN_BROADCAST ||
			   (dev->flags & IFF_POINTOPOINT)) {
			neigh->nud_state = NUD_NOARP;
			memcpy(neigh->ha, dev->broadcast, dev->addr_len);
		}

		if (dev->header_ops->cache)
			neigh->ops = &arp_hh_ops;
		else
			neigh->ops = &arp_generic_ops;

		if (neigh->nud_state & NUD_VALID)
			neigh->output = neigh->ops->connected_output;
		else
			neigh->output = neigh->ops->output;
	}
	return 0;
}