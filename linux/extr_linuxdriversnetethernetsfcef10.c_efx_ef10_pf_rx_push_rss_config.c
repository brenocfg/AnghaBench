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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_indir_table; int /*<<< orphan*/ * rx_hash_key; } ;
struct efx_nic {int rss_spread; int /*<<< orphan*/  net_dev; TYPE_1__ rss_context; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOBUFS ; 
 int efx_ef10_rx_push_exclusive_rss_config (struct efx_nic*,scalar_t__ const*,int /*<<< orphan*/  const*) ; 
 int efx_ef10_rx_push_shared_rss_config (struct efx_nic*,unsigned int*) ; 
 scalar_t__ const ethtool_rxfh_indir_default (size_t,int) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int efx_ef10_pf_rx_push_rss_config(struct efx_nic *efx, bool user,
					  const u32 *rx_indir_table,
					  const u8 *key)
{
	int rc;

	if (efx->rss_spread == 1)
		return 0;

	if (!key)
		key = efx->rss_context.rx_hash_key;

	rc = efx_ef10_rx_push_exclusive_rss_config(efx, rx_indir_table, key);

	if (rc == -ENOBUFS && !user) {
		unsigned context_size;
		bool mismatch = false;
		size_t i;

		for (i = 0;
		     i < ARRAY_SIZE(efx->rss_context.rx_indir_table) && !mismatch;
		     i++)
			mismatch = rx_indir_table[i] !=
				ethtool_rxfh_indir_default(i, efx->rss_spread);

		rc = efx_ef10_rx_push_shared_rss_config(efx, &context_size);
		if (rc == 0) {
			if (context_size != efx->rss_spread)
				netif_warn(efx, probe, efx->net_dev,
					   "Could not allocate an exclusive RSS"
					   " context; allocated a shared one of"
					   " different size."
					   " Wanted %u, got %u.\n",
					   efx->rss_spread, context_size);
			else if (mismatch)
				netif_warn(efx, probe, efx->net_dev,
					   "Could not allocate an exclusive RSS"
					   " context; allocated a shared one but"
					   " could not apply custom"
					   " indirection.\n");
			else
				netif_info(efx, probe, efx->net_dev,
					   "Could not allocate an exclusive RSS"
					   " context; allocated a shared one.\n");
		}
	}
	return rc;
}