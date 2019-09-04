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
 int /*<<< orphan*/  PN_CON_DATAIF_EN ; 
 int /*<<< orphan*/  USB3_PN_CON ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_enable_dma_pipen(struct renesas_usb3 *usb3)
{
	usb3_set_bit(usb3, PN_CON_DATAIF_EN, USB3_PN_CON);
}