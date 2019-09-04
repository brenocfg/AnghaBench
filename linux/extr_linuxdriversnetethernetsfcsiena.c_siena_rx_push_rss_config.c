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
typedef  int /*<<< orphan*/  temp ;
struct TYPE_2__ {int /*<<< orphan*/  const* rx_indir_table; int /*<<< orphan*/  const* rx_hash_key; } ;
struct efx_nic {TYPE_1__ rss_context; } ;
typedef  int /*<<< orphan*/  const efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_CZ_RX_RSS_IPV6_IP_THASH_ENABLE ; 
 int /*<<< orphan*/  FRF_CZ_RX_RSS_IPV6_THASH_ENABLE ; 
 scalar_t__ FRF_CZ_RX_RSS_IPV6_TKEY_HI_LBN ; 
 int FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH ; 
 int /*<<< orphan*/  FR_BZ_RX_RSS_TKEY ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG1 ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG2 ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG3 ; 
 int /*<<< orphan*/  efx_farch_rx_push_indir_table (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int siena_rx_push_rss_config(struct efx_nic *efx, bool user,
				    const u32 *rx_indir_table, const u8 *key)
{
	efx_oword_t temp;

	/* Set hash key for IPv4 */
	if (key)
		memcpy(efx->rss_context.rx_hash_key, key, sizeof(temp));
	memcpy(&temp, efx->rss_context.rx_hash_key, sizeof(temp));
	efx_writeo(efx, &temp, FR_BZ_RX_RSS_TKEY);

	/* Enable IPv6 RSS */
	BUILD_BUG_ON(sizeof(efx->rss_context.rx_hash_key) <
		     2 * sizeof(temp) + FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8 ||
		     FRF_CZ_RX_RSS_IPV6_TKEY_HI_LBN != 0);
	memcpy(&temp, efx->rss_context.rx_hash_key, sizeof(temp));
	efx_writeo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG1);
	memcpy(&temp, efx->rss_context.rx_hash_key + sizeof(temp), sizeof(temp));
	efx_writeo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG2);
	EFX_POPULATE_OWORD_2(temp, FRF_CZ_RX_RSS_IPV6_THASH_ENABLE, 1,
			     FRF_CZ_RX_RSS_IPV6_IP_THASH_ENABLE, 1);
	memcpy(&temp, efx->rss_context.rx_hash_key + 2 * sizeof(temp),
	       FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8);
	efx_writeo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG3);

	memcpy(efx->rss_context.rx_indir_table, rx_indir_table,
	       sizeof(efx->rss_context.rx_indir_table));
	efx_farch_rx_push_indir_table(efx);

	return 0;
}