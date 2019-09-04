#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  temp ;
struct ef4_nic {int /*<<< orphan*/ * rx_indir_table; int /*<<< orphan*/  const* rx_hash_key; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  FR_BZ_RX_RSS_TKEY ; 
 int /*<<< orphan*/  ef4_farch_rx_push_indir_table (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int falcon_b0_rx_push_rss_config(struct ef4_nic *efx, bool user,
					const u32 *rx_indir_table)
{
	ef4_oword_t temp;

	(void) user;
	/* Set hash key for IPv4 */
	memcpy(&temp, efx->rx_hash_key, sizeof(temp));
	ef4_writeo(efx, &temp, FR_BZ_RX_RSS_TKEY);

	memcpy(efx->rx_indir_table, rx_indir_table,
	       sizeof(efx->rx_indir_table));
	ef4_farch_rx_push_indir_table(efx);
	return 0;
}