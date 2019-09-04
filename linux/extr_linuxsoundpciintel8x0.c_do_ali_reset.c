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
struct intel8x0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_FIFOCR1 ; 
 int /*<<< orphan*/  ALI_FIFOCR2 ; 
 int /*<<< orphan*/  ALI_FIFOCR3 ; 
 int /*<<< orphan*/  ALI_INTERFACECR ; 
 int /*<<< orphan*/  ALI_INTERRUPTCR ; 
 int /*<<< orphan*/  ALI_INTERRUPTSR ; 
 int /*<<< orphan*/  ALI_SCR ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 int ICH_ALI_IF_PI ; 
 int ICH_ALI_IF_PO ; 
 int ICH_ALI_SC_RESET ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_ali_reset(struct intel8x0 *chip)
{
	iputdword(chip, ICHREG(ALI_SCR), ICH_ALI_SC_RESET);
	iputdword(chip, ICHREG(ALI_FIFOCR1), 0x83838383);
	iputdword(chip, ICHREG(ALI_FIFOCR2), 0x83838383);
	iputdword(chip, ICHREG(ALI_FIFOCR3), 0x83838383);
	iputdword(chip, ICHREG(ALI_INTERFACECR),
		  ICH_ALI_IF_PI|ICH_ALI_IF_PO);
	iputdword(chip, ICHREG(ALI_INTERRUPTCR), 0x00000000);
	iputdword(chip, ICHREG(ALI_INTERRUPTSR), 0x00000000);
}