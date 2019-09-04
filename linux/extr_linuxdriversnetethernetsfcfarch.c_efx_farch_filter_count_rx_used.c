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
typedef  scalar_t__ u32 ;
struct efx_nic {struct efx_farch_filter_state* filter_state; } ;
struct efx_farch_filter_table {unsigned int size; TYPE_1__* spec; int /*<<< orphan*/  used_bitmap; } ;
struct efx_farch_filter_state {int /*<<< orphan*/  lock; struct efx_farch_filter_table* table; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;
typedef  enum efx_farch_filter_table_id { ____Placeholder_efx_farch_filter_table_id } efx_farch_filter_table_id ;
struct TYPE_2__ {int priority; } ;

/* Variables and functions */
 int EFX_FARCH_FILTER_TABLE_RX_DEF ; 
 int EFX_FARCH_FILTER_TABLE_RX_IP ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

u32 efx_farch_filter_count_rx_used(struct efx_nic *efx,
				   enum efx_filter_priority priority)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	enum efx_farch_filter_table_id table_id;
	struct efx_farch_filter_table *table;
	unsigned int filter_idx;
	u32 count = 0;

	down_read(&state->lock);

	for (table_id = EFX_FARCH_FILTER_TABLE_RX_IP;
	     table_id <= EFX_FARCH_FILTER_TABLE_RX_DEF;
	     table_id++) {
		table = &state->table[table_id];
		for (filter_idx = 0; filter_idx < table->size; filter_idx++) {
			if (test_bit(filter_idx, table->used_bitmap) &&
			    table->spec[filter_idx].priority == priority)
				++count;
		}
	}

	up_read(&state->lock);

	return count;
}