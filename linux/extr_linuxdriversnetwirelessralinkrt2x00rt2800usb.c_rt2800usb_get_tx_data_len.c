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
struct queue_entry {TYPE_1__* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt2800usb_get_tx_data_len(struct queue_entry *entry)
{
	/*
	 * pad(1~3 bytes) is needed after each 802.11 payload.
	 * USB end pad(4 bytes) is needed at each USB bulk out packet end.
	 * TX frame format is :
	 * | TXINFO | TXWI | 802.11 header | L2 pad | payload | pad | USB end pad |
	 *                 |<------------- tx_pkt_len ------------->|
	 */

	return roundup(entry->skb->len, 4) + 4;
}