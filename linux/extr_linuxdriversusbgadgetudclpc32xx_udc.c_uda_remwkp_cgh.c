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
struct lpc32xx_udc {int dev_status; TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rmwk_chgb ) (int) ;} ;

/* Variables and functions */
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void uda_remwkp_cgh(struct lpc32xx_udc *udc)
{
	if (udc->board->rmwk_chgb != NULL)
		udc->board->rmwk_chgb(udc->dev_status &
				      (1 << USB_DEVICE_REMOTE_WAKEUP));
}