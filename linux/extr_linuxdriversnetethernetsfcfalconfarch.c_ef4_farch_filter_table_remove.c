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
struct ef4_nic {struct ef4_farch_filter_state* filter_state; } ;
struct ef4_farch_filter_state {TYPE_1__* table; } ;
typedef  enum ef4_farch_filter_table_id { ____Placeholder_ef4_farch_filter_table_id } ef4_farch_filter_table_id ;
struct TYPE_2__ {int /*<<< orphan*/  spec; struct ef4_farch_filter_state* used_bitmap; } ;

/* Variables and functions */
 int EF4_FARCH_FILTER_TABLE_COUNT ; 
 int /*<<< orphan*/  kfree (struct ef4_farch_filter_state*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void ef4_farch_filter_table_remove(struct ef4_nic *efx)
{
	struct ef4_farch_filter_state *state = efx->filter_state;
	enum ef4_farch_filter_table_id table_id;

	for (table_id = 0; table_id < EF4_FARCH_FILTER_TABLE_COUNT; table_id++) {
		kfree(state->table[table_id].used_bitmap);
		vfree(state->table[table_id].spec);
	}
	kfree(state);
}