#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ar5523 {TYPE_1__* rx_cmd_urb; int /*<<< orphan*/  rx_cmd_buf; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_MAX_RXCMDSZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static int ar5523_alloc_rx_cmd(struct ar5523 *ar)
{
	ar->rx_cmd_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!ar->rx_cmd_urb)
		return -ENOMEM;

	ar->rx_cmd_buf = usb_alloc_coherent(ar->dev, AR5523_MAX_RXCMDSZ,
					    GFP_KERNEL,
					    &ar->rx_cmd_urb->transfer_dma);
	if (!ar->rx_cmd_buf) {
		usb_free_urb(ar->rx_cmd_urb);
		return -ENOMEM;
	}
	return 0;
}