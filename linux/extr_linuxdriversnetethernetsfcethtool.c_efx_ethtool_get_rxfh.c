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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_hash_key; int /*<<< orphan*/  rx_indir_table; } ;
struct efx_nic {TYPE_1__* type; TYPE_2__ rss_context; } ;
struct TYPE_3__ {int (* rx_pull_rss_config ) (struct efx_nic*) ;int rx_hash_key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*) ; 

__attribute__((used)) static int efx_ethtool_get_rxfh(struct net_device *net_dev, u32 *indir, u8 *key,
				u8 *hfunc)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	int rc;

	rc = efx->type->rx_pull_rss_config(efx);
	if (rc)
		return rc;

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	if (indir)
		memcpy(indir, efx->rss_context.rx_indir_table,
		       sizeof(efx->rss_context.rx_indir_table));
	if (key)
		memcpy(key, efx->rss_context.rx_hash_key,
		       efx->type->rx_hash_key_size);
	return 0;
}