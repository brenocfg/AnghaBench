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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct macsec_secy {int dummy; } ;
struct macsec_rx_sc {int dummy; } ;
typedef  int /*<<< orphan*/  sci_t ;
struct TYPE_2__ {struct macsec_secy secy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct macsec_rx_sc* ERR_CAST (struct net_device*) ; 
 struct macsec_rx_sc* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 size_t MACSEC_RXSC_ATTR_SCI ; 
 struct macsec_rx_sc* find_rx_sc_rtnl (struct macsec_secy*,int /*<<< orphan*/ ) ; 
 struct net_device* get_dev_from_nl (struct net*,struct nlattr**) ; 
 TYPE_1__* macsec_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_sci (struct nlattr*) ; 

__attribute__((used)) static struct macsec_rx_sc *get_rxsc_from_nl(struct net *net,
					     struct nlattr **attrs,
					     struct nlattr **tb_rxsc,
					     struct net_device **devp,
					     struct macsec_secy **secyp)
{
	struct net_device *dev;
	struct macsec_secy *secy;
	struct macsec_rx_sc *rx_sc;
	sci_t sci;

	dev = get_dev_from_nl(net, attrs);
	if (IS_ERR(dev))
		return ERR_CAST(dev);

	secy = &macsec_priv(dev)->secy;

	if (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		return ERR_PTR(-EINVAL);

	sci = nla_get_sci(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);
	rx_sc = find_rx_sc_rtnl(secy, sci);
	if (!rx_sc)
		return ERR_PTR(-ENODEV);

	*secyp = secy;
	*devp = dev;

	return rx_sc;
}