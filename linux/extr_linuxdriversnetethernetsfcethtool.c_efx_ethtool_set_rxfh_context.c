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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct efx_rss_context {scalar_t__* rx_hash_key; int /*<<< orphan*/  user_id; int /*<<< orphan*/ * rx_indir_table; int /*<<< orphan*/  context_id; } ;
struct efx_nic {int /*<<< orphan*/  rss_lock; TYPE_1__* type; } ;
struct TYPE_2__ {int (* rx_push_rss_context_config ) (struct efx_nic*,struct efx_rss_context*,int /*<<< orphan*/  const*,scalar_t__ const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EF10_RSS_CONTEXT_INVALID ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  ETH_RXFH_CONTEXT_ALLOC ; 
 struct efx_rss_context* efx_alloc_rss_context_entry (struct efx_nic*) ; 
 struct efx_rss_context* efx_find_rss_context_entry (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_free_rss_context_entry (struct efx_rss_context*) ; 
 int /*<<< orphan*/  efx_set_default_rx_indir_table (struct efx_nic*,struct efx_rss_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (scalar_t__*,int) ; 
 int stub1 (struct efx_nic*,struct efx_rss_context*,int /*<<< orphan*/  const*,scalar_t__ const*) ; 
 int stub2 (struct efx_nic*,struct efx_rss_context*,int /*<<< orphan*/  const*,scalar_t__ const*) ; 

__attribute__((used)) static int efx_ethtool_set_rxfh_context(struct net_device *net_dev,
					const u32 *indir, const u8 *key,
					const u8 hfunc, u32 *rss_context,
					bool delete)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_rss_context *ctx;
	bool allocated = false;
	int rc;

	if (!efx->type->rx_push_rss_context_config)
		return -EOPNOTSUPP;
	/* Hash function is Toeplitz, cannot be changed */
	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	mutex_lock(&efx->rss_lock);

	if (*rss_context == ETH_RXFH_CONTEXT_ALLOC) {
		if (delete) {
			/* alloc + delete == Nothing to do */
			rc = -EINVAL;
			goto out_unlock;
		}
		ctx = efx_alloc_rss_context_entry(efx);
		if (!ctx) {
			rc = -ENOMEM;
			goto out_unlock;
		}
		ctx->context_id = EFX_EF10_RSS_CONTEXT_INVALID;
		/* Initialise indir table and key to defaults */
		efx_set_default_rx_indir_table(efx, ctx);
		netdev_rss_key_fill(ctx->rx_hash_key, sizeof(ctx->rx_hash_key));
		allocated = true;
	} else {
		ctx = efx_find_rss_context_entry(efx, *rss_context);
		if (!ctx) {
			rc = -ENOENT;
			goto out_unlock;
		}
	}

	if (delete) {
		/* delete this context */
		rc = efx->type->rx_push_rss_context_config(efx, ctx, NULL, NULL);
		if (!rc)
			efx_free_rss_context_entry(ctx);
		goto out_unlock;
	}

	if (!key)
		key = ctx->rx_hash_key;
	if (!indir)
		indir = ctx->rx_indir_table;

	rc = efx->type->rx_push_rss_context_config(efx, ctx, indir, key);
	if (rc && allocated)
		efx_free_rss_context_entry(ctx);
	else
		*rss_context = ctx->user_id;
out_unlock:
	mutex_unlock(&efx->rss_lock);
	return rc;
}