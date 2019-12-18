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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct ipc_message {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 

void skl_ipc_tx_data_copy(struct ipc_message *msg, char *tx_data,
		size_t tx_size)
{
	if (tx_size)
		memcpy(msg->tx.data, tx_data, tx_size);
}