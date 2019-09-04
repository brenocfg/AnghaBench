#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int min_mtu; int ifindex; int /*<<< orphan*/  name; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mtu; } ;
struct gsm_netconfig {scalar_t__ protocol; int adaption; char* if_name; } ;
struct gsm_mux_net {int /*<<< orphan*/  ref; struct gsm_dlci* dlci; } ;
struct gsm_dlci {int adaption; int prev_adaption; struct net_device* net; int /*<<< orphan*/  data; int /*<<< orphan*/  prev_data; TYPE_1__* gsm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EPERM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlci_net_free (struct gsm_dlci*) ; 
 int /*<<< orphan*/  gsm_mux_net_init ; 
 int /*<<< orphan*/  gsm_mux_rx_netchar ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gsm_mux_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsm_create_network(struct gsm_dlci *dlci, struct gsm_netconfig *nc)
{
	char *netname;
	int retval = 0;
	struct net_device *net;
	struct gsm_mux_net *mux_net;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	/* Already in a non tty mode */
	if (dlci->adaption > 2)
		return -EBUSY;

	if (nc->protocol != htons(ETH_P_IP))
		return -EPROTONOSUPPORT;

	if (nc->adaption != 3 && nc->adaption != 4)
		return -EPROTONOSUPPORT;

	pr_debug("create network interface");

	netname = "gsm%d";
	if (nc->if_name[0] != '\0')
		netname = nc->if_name;
	net = alloc_netdev(sizeof(struct gsm_mux_net), netname,
			   NET_NAME_UNKNOWN, gsm_mux_net_init);
	if (!net) {
		pr_err("alloc_netdev failed");
		return -ENOMEM;
	}
	net->mtu = dlci->gsm->mtu;
	net->min_mtu = 8;
	net->max_mtu = dlci->gsm->mtu;
	mux_net = netdev_priv(net);
	mux_net->dlci = dlci;
	kref_init(&mux_net->ref);
	strncpy(nc->if_name, net->name, IFNAMSIZ); /* return net name */

	/* reconfigure dlci for network */
	dlci->prev_adaption = dlci->adaption;
	dlci->prev_data = dlci->data;
	dlci->adaption = nc->adaption;
	dlci->data = gsm_mux_rx_netchar;
	dlci->net = net;

	pr_debug("register netdev");
	retval = register_netdev(net);
	if (retval) {
		pr_err("network register fail %d\n", retval);
		dlci_net_free(dlci);
		return retval;
	}
	return net->ifindex;	/* return network index */
}