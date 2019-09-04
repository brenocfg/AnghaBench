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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_USB_INT_ENA_2 ; 
 int /*<<< orphan*/  USB_INT_2_PIPE (int) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_enable_pipe_irq(struct renesas_usb3 *usb3, int num)
{
	usb3_set_bit(usb3, USB_INT_2_PIPE(num), USB3_USB_INT_ENA_2);
}