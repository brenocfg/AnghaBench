#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pfile; } ;
struct netdevsim {int /*<<< orphan*/  ddir; TYPE_1__ ipsec; TYPE_2__* netdev; } ;
struct TYPE_4__ {int features; int hw_enc_features; int /*<<< orphan*/ * xfrmdev_ops; } ;

/* Variables and functions */
 int NETIF_F_GSO_ESP ; 
 int NETIF_F_HW_ESP ; 
 int NETIF_F_HW_ESP_TX_CSUM ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct netdevsim*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipsec_dbg_fops ; 
 int /*<<< orphan*/  nsim_xfrmdev_ops ; 

void nsim_ipsec_init(struct netdevsim *ns)
{
	ns->netdev->xfrmdev_ops = &nsim_xfrmdev_ops;

#define NSIM_ESP_FEATURES	(NETIF_F_HW_ESP | \
				 NETIF_F_HW_ESP_TX_CSUM | \
				 NETIF_F_GSO_ESP)

	ns->netdev->features |= NSIM_ESP_FEATURES;
	ns->netdev->hw_enc_features |= NSIM_ESP_FEATURES;

	ns->ipsec.pfile = debugfs_create_file("ipsec", 0400, ns->ddir, ns,
					      &ipsec_dbg_fops);
}