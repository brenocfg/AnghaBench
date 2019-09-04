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
struct r8152 {int /*<<< orphan*/  rx_queue; TYPE_1__* rx_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int RTL8152_MAX_RX ; 
 int /*<<< orphan*/  __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl_stop_rx(struct r8152 *tp)
{
	int i;

	for (i = 0; i < RTL8152_MAX_RX; i++)
		usb_kill_urb(tp->rx_info[i].urb);

	while (!skb_queue_empty(&tp->rx_queue))
		dev_kfree_skb(__skb_dequeue(&tp->rx_queue));

	return 0;
}