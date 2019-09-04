#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int lmc_gpio_io; int /*<<< orphan*/  lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 int TULIP_GP_PINSET ; 
 int /*<<< orphan*/  csr_gp ; 
 int /*<<< orphan*/  lmc_trace (int /*<<< orphan*/ ,char*) ; 

void lmc_gpio_mkoutput(lmc_softc_t * const sc, u32 bits) /*fold00*/
{
    lmc_trace(sc->lmc_device, "lmc_gpio_mkoutput in");
    sc->lmc_gpio_io |= bits;
    LMC_CSR_WRITE(sc, csr_gp, TULIP_GP_PINSET | (sc->lmc_gpio_io));
    lmc_trace(sc->lmc_device, "lmc_gpio_mkoutput out");
}