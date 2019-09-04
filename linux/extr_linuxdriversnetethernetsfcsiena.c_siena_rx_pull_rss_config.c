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
typedef  int /*<<< orphan*/  temp ;
struct TYPE_2__ {scalar_t__ rx_hash_key; } ;
struct efx_nic {TYPE_1__ rss_context; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG1 ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG2 ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG3 ; 
 int /*<<< orphan*/  efx_farch_rx_pull_indir_table (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int siena_rx_pull_rss_config(struct efx_nic *efx)
{
	efx_oword_t temp;

	/* Read from IPv6 RSS key as that's longer (the IPv4 key is just the
	 * first 128 bits of the same key, assuming it's been set by
	 * siena_rx_push_rss_config, below)
	 */
	efx_reado(efx, &temp, FR_CZ_RX_RSS_IPV6_REG1);
	memcpy(efx->rss_context.rx_hash_key, &temp, sizeof(temp));
	efx_reado(efx, &temp, FR_CZ_RX_RSS_IPV6_REG2);
	memcpy(efx->rss_context.rx_hash_key + sizeof(temp), &temp, sizeof(temp));
	efx_reado(efx, &temp, FR_CZ_RX_RSS_IPV6_REG3);
	memcpy(efx->rss_context.rx_hash_key + 2 * sizeof(temp), &temp,
	       FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8);
	efx_farch_rx_pull_indir_table(efx);
	return 0;
}