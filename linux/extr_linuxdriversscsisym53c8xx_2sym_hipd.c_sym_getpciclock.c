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
struct sym_hcb {int features; int pciclk_khz; } ;

/* Variables and functions */
 int FE_66MHZ ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK ; 
 int /*<<< orphan*/  nc_stest1 ; 
 int sym_getfreq (struct sym_hcb*) ; 

__attribute__((used)) static int sym_getpciclock (struct sym_hcb *np)
{
	int f = 0;

	/*
	 *  For now, we only need to know about the actual 
	 *  PCI BUS clock frequency for C1010-66 chips.
	 */
#if 1
	if (np->features & FE_66MHZ) {
#else
	if (1) {
#endif
		OUTB(np, nc_stest1, SCLK); /* Use the PCI clock as SCSI clock */
		f = sym_getfreq(np);
		OUTB(np, nc_stest1, 0);
	}
	np->pciclk_khz = f;

	return f;
}