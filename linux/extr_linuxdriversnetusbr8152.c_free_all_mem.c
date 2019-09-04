#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r8152 {int /*<<< orphan*/ * intr_buff; int /*<<< orphan*/ * intr_urb; TYPE_2__* tx_info; TYPE_1__* rx_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * head; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * urb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * head; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int RTL8152_MAX_RX ; 
 int RTL8152_MAX_TX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_all_mem(struct r8152 *tp)
{
	int i;

	for (i = 0; i < RTL8152_MAX_RX; i++) {
		usb_free_urb(tp->rx_info[i].urb);
		tp->rx_info[i].urb = NULL;

		kfree(tp->rx_info[i].buffer);
		tp->rx_info[i].buffer = NULL;
		tp->rx_info[i].head = NULL;
	}

	for (i = 0; i < RTL8152_MAX_TX; i++) {
		usb_free_urb(tp->tx_info[i].urb);
		tp->tx_info[i].urb = NULL;

		kfree(tp->tx_info[i].buffer);
		tp->tx_info[i].buffer = NULL;
		tp->tx_info[i].head = NULL;
	}

	usb_free_urb(tp->intr_urb);
	tp->intr_urb = NULL;

	kfree(tp->intr_buff);
	tp->intr_buff = NULL;
}