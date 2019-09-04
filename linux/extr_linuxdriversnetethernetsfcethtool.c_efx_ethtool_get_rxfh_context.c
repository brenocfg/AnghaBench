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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct efx_rss_context {int /*<<< orphan*/  rx_hash_key; int /*<<< orphan*/  rx_indir_table; } ;
struct efx_nic {int /*<<< orphan*/  rss_lock; TYPE_1__* type; } ;
struct TYPE_2__ {int (* rx_pull_rss_context_config ) (struct efx_nic*,struct efx_rss_context*) ;int rx_hash_key_size; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 struct efx_rss_context* efx_find_rss_context_entry (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*,struct efx_rss_context*) ; 

__attribute__((used)) static int efx_ethtool_get_rxfh_context(struct net_device *net_dev, u32 *indir,
					u8 *key, u8 *hfunc, u32 rss_context)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_rss_context *ctx;
	int rc = 0;

	if (!efx->type->rx_pull_rss_context_config)
		return -EOPNOTSUPP;

	mutex_lock(&efx->rss_lock);
	ctx = efx_find_rss_context_entry(efx, rss_context);
	if (!ctx) {
		rc = -ENOENT;
		goto out_unlock;
	}
	rc = efx->type->rx_pull_rss_context_config(efx, ctx);
	if (rc)
		goto out_unlock;

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	if (indir)
		memcpy(indir, ctx->rx_indir_table, sizeof(ctx->rx_indir_table));
	if (key)
		memcpy(key, ctx->rx_hash_key, efx->type->rx_hash_key_size);
out_unlock:
	mutex_unlock(&efx->rss_lock);
	return rc;
}