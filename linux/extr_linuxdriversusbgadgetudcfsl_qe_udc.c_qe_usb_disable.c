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
struct qe_udc {TYPE_1__* usb_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_usmod; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_MODE_EN ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qe_usb_disable(struct qe_udc *udc)
{
	clrbits8(&udc->usb_regs->usb_usmod, USB_MODE_EN);
}