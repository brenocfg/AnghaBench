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
typedef  int /*<<< orphan*/  u32 ;
struct at91_udc {int /*<<< orphan*/  matrix; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91SAM9261_MATRIX_USBPUCR ; 
 int /*<<< orphan*/  AT91_MATRIX_USBPUCR_PUON ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91sam9261_udc_pullup(struct at91_udc *udc, int is_on)
{
	u32 usbpucr = 0;

	if (is_on)
		usbpucr = AT91_MATRIX_USBPUCR_PUON;

	regmap_update_bits(udc->matrix, AT91SAM9261_MATRIX_USBPUCR,
			   AT91_MATRIX_USBPUCR_PUON, usbpucr);
}