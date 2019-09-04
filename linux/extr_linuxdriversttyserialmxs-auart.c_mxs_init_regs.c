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
struct mxs_auart_port {int /*<<< orphan*/ * vendor; } ;

/* Variables and functions */
 scalar_t__ is_asm9260_auart (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  vendor_alphascale_asm9260 ; 
 int /*<<< orphan*/  vendor_freescale_stmp37xx ; 

__attribute__((used)) static void mxs_init_regs(struct mxs_auart_port *s)
{
	if (is_asm9260_auart(s))
		s->vendor = &vendor_alphascale_asm9260;
	else
		s->vendor = &vendor_freescale_stmp37xx;
}