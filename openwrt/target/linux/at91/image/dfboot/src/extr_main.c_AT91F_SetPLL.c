#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  CKGR_PLLAR; } ;
struct TYPE_5__ {int PMC_IDR; int PMC_MCKR; } ;
typedef  int AT91_REG ;
typedef  TYPE_1__* AT91PS_PMC ;
typedef  TYPE_2__* AT91PS_CKGR ;

/* Variables and functions */
 TYPE_2__* AT91C_BASE_CKGR ; 
 TYPE_1__* AT91C_BASE_PMC ; 
 int /*<<< orphan*/  AT91C_PLLA_VALUE ; 
 int AT91C_PMC_LOCKA ; 
 int AT91C_PMC_MCKRDY ; 
 int* AT91C_PMC_SR ; 

__attribute__((used)) static unsigned int AT91F_SetPLL(void)
{
	AT91_REG tmp;
	AT91PS_PMC pPmc = AT91C_BASE_PMC;
	AT91PS_CKGR pCkgr = AT91C_BASE_CKGR;

	pPmc->PMC_IDR = 0xFFFFFFFF;

	/* -Setup the PLL A */
	pCkgr->CKGR_PLLAR = AT91C_PLLA_VALUE;

	while (!(*AT91C_PMC_SR & AT91C_PMC_LOCKA));
	
	/* - Switch Master Clock from PLLB to PLLA/3 */
	tmp = pPmc->PMC_MCKR;
	/* See Atmel Errata #27 and #28 */
	if (tmp & 0x0000001C) {
		tmp = (tmp & ~0x0000001C);
		pPmc->PMC_MCKR = tmp;
		while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY));
	}
	if (tmp != 0x00000202) {
		pPmc->PMC_MCKR = 0x00000202;
		if ((tmp & 0x00000003) != 0x00000002)
			while (!(*AT91C_PMC_SR & AT91C_PMC_MCKRDY));
	}

	return 1;	
}