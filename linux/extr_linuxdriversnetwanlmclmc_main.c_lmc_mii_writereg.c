#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LMC_MII_SYNC (TYPE_1__* const) ; 
 int /*<<< orphan*/  csr_9 ; 
 int /*<<< orphan*/  lmc_delay () ; 
 int /*<<< orphan*/  lmc_trace (int /*<<< orphan*/ ,char*) ; 

void lmc_mii_writereg (lmc_softc_t * const sc, unsigned devaddr, unsigned regno, unsigned data) /*fold00*/
{
    int i = 32;
    int command = (0x5002 << 16) | (devaddr << 23) | (regno << 18) | data;

    lmc_trace(sc->lmc_device, "lmc_mii_writereg in");

    LMC_MII_SYNC (sc);

    i = 31;
    while (i >= 0)
    {
        int datav;

        if (command & (1 << i))
            datav = 0x20000;
        else
            datav = 0x00000;

        LMC_CSR_WRITE (sc, csr_9, datav);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        LMC_CSR_WRITE (sc, csr_9, (datav | 0x10000));
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        i--;
    }

    i = 2;
    while (i > 0)
    {
        LMC_CSR_WRITE (sc, csr_9, 0x40000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        LMC_CSR_WRITE (sc, csr_9, 0x50000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        i--;
    }

    lmc_trace(sc->lmc_device, "lmc_mii_writereg out");
}