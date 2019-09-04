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
typedef  int u32 ;
struct ipc_message {int header; int tx_size; scalar_t__ tx_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 

__attribute__((used)) static void byt_tx_data_copy(struct ipc_message *msg, char *tx_data,
	size_t tx_size)
{
	/* msg content = lower 32-bit of the header + data */
	*(u32 *)msg->tx_data = (u32)(msg->header & (u32)-1);
	memcpy(msg->tx_data + sizeof(u32), tx_data, tx_size);
	msg->tx_size += sizeof(u32);
}