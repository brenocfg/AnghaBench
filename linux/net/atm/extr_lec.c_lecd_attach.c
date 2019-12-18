#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lec_priv {int itfnum; int maximum_unknown_frame_count; int max_unknown_frame_time; int vcc_timeout_period; int max_retry_count; int aging_time; int forward_delay_time; int arp_response_time; int flush_timeout; int path_switching_delay; scalar_t__ topology_change; struct atm_vcc* lecd; } ;
struct atm_vcc {int /*<<< orphan*/  flags; TYPE_1__* proto_data; int /*<<< orphan*/ * dev; } ;
struct TYPE_7__ {int max_mtu; int flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_META ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int HZ ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int MAX_LEC_ITF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* alloc_etherdev (int) ; 
 int array_index_nospec (int,int) ; 
 TYPE_1__** dev_lec ; 
 int /*<<< orphan*/  free_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  lec_arp_init (struct lec_priv*) ; 
 int /*<<< orphan*/  lec_netdev_ops ; 
 int /*<<< orphan*/  lecatm_dev ; 
 struct lec_priv* netdev_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_start_queue (TYPE_1__*) ; 
 scalar_t__ register_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vcc_insert_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lecd_attach(struct atm_vcc *vcc, int arg)
{
	int i;
	struct lec_priv *priv;

	if (arg < 0)
		arg = 0;
	if (arg >= MAX_LEC_ITF)
		return -EINVAL;
	i = array_index_nospec(arg, MAX_LEC_ITF);
	if (!dev_lec[i]) {
		int size;

		size = sizeof(struct lec_priv);
		dev_lec[i] = alloc_etherdev(size);
		if (!dev_lec[i])
			return -ENOMEM;
		dev_lec[i]->netdev_ops = &lec_netdev_ops;
		dev_lec[i]->max_mtu = 18190;
		snprintf(dev_lec[i]->name, IFNAMSIZ, "lec%d", i);
		if (register_netdev(dev_lec[i])) {
			free_netdev(dev_lec[i]);
			return -EINVAL;
		}

		priv = netdev_priv(dev_lec[i]);
	} else {
		priv = netdev_priv(dev_lec[i]);
		if (priv->lecd)
			return -EADDRINUSE;
	}
	lec_arp_init(priv);
	priv->itfnum = i;	/* LANE2 addition */
	priv->lecd = vcc;
	vcc->dev = &lecatm_dev;
	vcc_insert_socket(sk_atm(vcc));

	vcc->proto_data = dev_lec[i];
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	/* Set default values to these variables */
	priv->maximum_unknown_frame_count = 1;
	priv->max_unknown_frame_time = (1 * HZ);
	priv->vcc_timeout_period = (1200 * HZ);
	priv->max_retry_count = 1;
	priv->aging_time = (300 * HZ);
	priv->forward_delay_time = (15 * HZ);
	priv->topology_change = 0;
	priv->arp_response_time = (1 * HZ);
	priv->flush_timeout = (4 * HZ);
	priv->path_switching_delay = (6 * HZ);

	if (dev_lec[i]->flags & IFF_UP)
		netif_start_queue(dev_lec[i]);
	__module_get(THIS_MODULE);
	return i;
}