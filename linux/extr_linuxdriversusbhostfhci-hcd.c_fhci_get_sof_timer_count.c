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
typedef  int /*<<< orphan*/  u16 ;
struct fhci_usb {TYPE_2__* fhci; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_ussft; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int) ; 
 int in_be16 (int /*<<< orphan*/ *) ; 

u16 fhci_get_sof_timer_count(struct fhci_usb *usb)
{
	return be16_to_cpu(in_be16(&usb->fhci->regs->usb_ussft) / 12);
}