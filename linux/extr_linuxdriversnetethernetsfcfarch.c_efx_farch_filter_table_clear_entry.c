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
struct efx_nic {int dummy; } ;
struct efx_farch_filter_table {scalar_t__ offset; scalar_t__ used; unsigned int step; scalar_t__ id; int /*<<< orphan*/ * search_limit; int /*<<< orphan*/ * spec; int /*<<< orphan*/  used_bitmap; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EFX_FARCH_FILTER_TABLE_TX_MAC ; 
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_farch_filter_push_rx_config (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_farch_filter_push_tx_limits (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
efx_farch_filter_table_clear_entry(struct efx_nic *efx,
				   struct efx_farch_filter_table *table,
				   unsigned int filter_idx)
{
	static efx_oword_t filter;

	EFX_WARN_ON_PARANOID(!test_bit(filter_idx, table->used_bitmap));
	BUG_ON(table->offset == 0); /* can't clear MAC default filters */

	__clear_bit(filter_idx, table->used_bitmap);
	--table->used;
	memset(&table->spec[filter_idx], 0, sizeof(table->spec[0]));

	efx_writeo(efx, &filter, table->offset + table->step * filter_idx);

	/* If this filter required a greater search depth than
	 * any other, the search limit for its type can now be
	 * decreased.  However, it is hard to determine that
	 * unless the table has become completely empty - in
	 * which case, all its search limits can be set to 0.
	 */
	if (unlikely(table->used == 0)) {
		memset(table->search_limit, 0, sizeof(table->search_limit));
		if (table->id == EFX_FARCH_FILTER_TABLE_TX_MAC)
			efx_farch_filter_push_tx_limits(efx);
		else
			efx_farch_filter_push_rx_config(efx);
	}
}