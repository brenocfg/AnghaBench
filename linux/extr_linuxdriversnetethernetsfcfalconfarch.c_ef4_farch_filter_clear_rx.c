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
struct ef4_nic {int dummy; } ;
typedef  enum ef4_filter_priority { ____Placeholder_ef4_filter_priority } ef4_filter_priority ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_FARCH_FILTER_TABLE_RX_DEF ; 
 int /*<<< orphan*/  EF4_FARCH_FILTER_TABLE_RX_IP ; 
 int /*<<< orphan*/  EF4_FARCH_FILTER_TABLE_RX_MAC ; 
 int /*<<< orphan*/  ef4_farch_filter_table_clear (struct ef4_nic*,int /*<<< orphan*/ ,int) ; 

int ef4_farch_filter_clear_rx(struct ef4_nic *efx,
			       enum ef4_filter_priority priority)
{
	ef4_farch_filter_table_clear(efx, EF4_FARCH_FILTER_TABLE_RX_IP,
				     priority);
	ef4_farch_filter_table_clear(efx, EF4_FARCH_FILTER_TABLE_RX_MAC,
				     priority);
	ef4_farch_filter_table_clear(efx, EF4_FARCH_FILTER_TABLE_RX_DEF,
				     priority);
	return 0;
}