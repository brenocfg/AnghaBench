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
struct TYPE_2__ {unsigned int conn_table; } ;

/* Variables and functions */
 int MAX_PVC_NUMBER ; 
 int /*<<< orphan*/  free_tx_ring (int) ; 
 TYPE_1__ g_atm_priv_data ; 

__attribute__((used)) static void mailbox_tx_handler(unsigned int queue_bitmap)
{
	int i;
	int bit;

	/* only get valid queues */
	queue_bitmap &= g_atm_priv_data.conn_table;

	for ( i = 0, bit = 1; i < MAX_PVC_NUMBER; i++, bit <<= 1 ) {
		if (queue_bitmap & bit)
			free_tx_ring(i);
	}
}