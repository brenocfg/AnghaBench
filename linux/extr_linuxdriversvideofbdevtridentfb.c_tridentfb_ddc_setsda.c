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
struct tridentfb_par {int /*<<< orphan*/  io_virt; } ;

/* Variables and functions */
 unsigned char DDC_MASK ; 
 unsigned char DDC_SDA_OUT ; 
 int /*<<< orphan*/  I2C ; 
 unsigned char vga_mm_rcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_mm_wcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void tridentfb_ddc_setsda(void *data, int val)
{
	struct tridentfb_par *par = data;
	unsigned char reg;

	reg = vga_mm_rcrt(par->io_virt, I2C) & DDC_MASK;
	if (!val)
		reg |= DDC_SDA_OUT;
	else
		reg &= ~DDC_SDA_OUT;
	vga_mm_wcrt(par->io_virt, I2C, reg);
}