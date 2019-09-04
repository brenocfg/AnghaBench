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
struct TYPE_2__ {scalar_t__ buffer; } ;
struct zd_usb_interrupt {TYPE_1__ read_regs; } ;
struct usb_int_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct usb_int_regs *get_read_regs(struct zd_usb_interrupt *intr)
{
	return (struct usb_int_regs *)intr->read_regs.buffer;
}