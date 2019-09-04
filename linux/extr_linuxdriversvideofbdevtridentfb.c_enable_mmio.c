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
struct tridentfb_par {int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NewMode1 ; 
 int PCIReg ; 
 int /*<<< orphan*/  Protection ; 
 int inb (int) ; 
 int /*<<< orphan*/  is_oldprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  vga_io_rseq (int) ; 
 int /*<<< orphan*/  vga_io_wseq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_mmio(struct tridentfb_par *par)
{
	/* Goto New Mode */
	vga_io_rseq(0x0B);

	/* Unprotect registers */
	vga_io_wseq(NewMode1, 0x80);
	if (!is_oldprotect(par->chip_id))
		vga_io_wseq(Protection, 0x92);

	/* Enable MMIO */
	outb(PCIReg, 0x3D4);
	outb(inb(0x3D5) | 0x01, 0x3D5);
}