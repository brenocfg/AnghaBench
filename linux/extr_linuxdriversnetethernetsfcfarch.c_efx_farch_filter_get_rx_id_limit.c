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
typedef  unsigned int u32 ;
struct efx_nic {struct efx_farch_filter_state* filter_state; } ;
struct efx_farch_filter_state {TYPE_1__* table; } ;
typedef  enum efx_farch_filter_table_id { ____Placeholder_efx_farch_filter_table_id } efx_farch_filter_table_id ;
struct TYPE_2__ {unsigned int size; } ;

/* Variables and functions */
 unsigned int EFX_FARCH_FILTER_INDEX_WIDTH ; 
 int EFX_FARCH_FILTER_MATCH_PRI_COUNT ; 
 int* efx_farch_filter_range_table ; 

u32 efx_farch_filter_get_rx_id_limit(struct efx_nic *efx)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	unsigned int range = EFX_FARCH_FILTER_MATCH_PRI_COUNT - 1;
	enum efx_farch_filter_table_id table_id;

	do {
		table_id = efx_farch_filter_range_table[range];
		if (state->table[table_id].size != 0)
			return range << EFX_FARCH_FILTER_INDEX_WIDTH |
				state->table[table_id].size;
	} while (range--);

	return 0;
}