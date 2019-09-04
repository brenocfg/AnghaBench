#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int lmc_gpio; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int LMC_GEP_CLK ; 
 int LMC_GEP_DATA ; 
 int LMC_GEP_SSI_GENERATOR ; 
 int /*<<< orphan*/  csr_gp ; 
 int /*<<< orphan*/  lmc_gpio_mkinput (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lmc_gpio_mkoutput (TYPE_1__*,int) ; 
 int /*<<< orphan*/  write_av9110_bit (TYPE_1__*,int) ; 

__attribute__((used)) static void write_av9110(lmc_softc_t *sc, u32 n, u32 m, u32 v, u32 x, u32 r)
{
  int i;

#if 0
  printk (LMC_PRINTF_FMT ": speed %u, %d %d %d %d %d\n",
	  LMC_PRINTF_ARGS, sc->ictl.clock_rate, n, m, v, x, r);
#endif

  sc->lmc_gpio |= LMC_GEP_SSI_GENERATOR;
  sc->lmc_gpio &= ~(LMC_GEP_DATA | LMC_GEP_CLK);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * Set the TXCLOCK, GENERATOR, SERIAL, and SERIALCLK
   * as outputs.
   */
  lmc_gpio_mkoutput (sc, (LMC_GEP_DATA | LMC_GEP_CLK
			  | LMC_GEP_SSI_GENERATOR));

  sc->lmc_gpio &= ~(LMC_GEP_SSI_GENERATOR);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * a shifting we will go...
   */
  for (i = 0; i < 7; i++)
    write_av9110_bit (sc, n >> i);
  for (i = 0; i < 7; i++)
    write_av9110_bit (sc, m >> i);
  for (i = 0; i < 1; i++)
    write_av9110_bit (sc, v >> i);
  for (i = 0; i < 2; i++)
    write_av9110_bit (sc, x >> i);
  for (i = 0; i < 2; i++)
    write_av9110_bit (sc, r >> i);
  for (i = 0; i < 5; i++)
    write_av9110_bit (sc, 0x17 >> i);

  /*
   * stop driving serial-related signals
   */
  lmc_gpio_mkinput (sc,
		    (LMC_GEP_DATA | LMC_GEP_CLK
		     | LMC_GEP_SSI_GENERATOR));
}