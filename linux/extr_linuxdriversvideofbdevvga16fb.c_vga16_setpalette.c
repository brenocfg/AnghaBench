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

/* Variables and functions */
 int /*<<< orphan*/  VGA_PEL_D ; 
 int /*<<< orphan*/  VGA_PEL_IW ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vga16_setpalette(int regno, unsigned red, unsigned green, unsigned blue)
{
	outb(regno,       VGA_PEL_IW);
	outb(red   >> 10, VGA_PEL_D);
	outb(green >> 10, VGA_PEL_D);
	outb(blue  >> 10, VGA_PEL_D);
}