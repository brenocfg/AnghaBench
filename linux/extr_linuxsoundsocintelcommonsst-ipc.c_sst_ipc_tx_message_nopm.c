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
typedef  int /*<<< orphan*/  u64 ;
struct sst_generic_ipc {int dummy; } ;

/* Variables and functions */
 int ipc_tx_message (struct sst_generic_ipc*,int /*<<< orphan*/ ,void*,size_t,void*,size_t,int) ; 

int sst_ipc_tx_message_nopm(struct sst_generic_ipc *ipc, u64 header,
	void *tx_data, size_t tx_bytes, void *rx_data, size_t rx_bytes)
{
	return ipc_tx_message(ipc, header, tx_data, tx_bytes,
		rx_data, rx_bytes, 1);
}