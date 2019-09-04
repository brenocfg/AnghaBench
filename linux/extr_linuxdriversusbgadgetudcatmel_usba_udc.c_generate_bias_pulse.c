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
struct usba_udc {int bias_pulse_needed; TYPE_1__* errata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pulse_bias ) (struct usba_udc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usba_udc*) ; 

__attribute__((used)) static void generate_bias_pulse(struct usba_udc *udc)
{
	if (!udc->bias_pulse_needed)
		return;

	if (udc->errata && udc->errata->pulse_bias)
		udc->errata->pulse_bias(udc);

	udc->bias_pulse_needed = false;
}