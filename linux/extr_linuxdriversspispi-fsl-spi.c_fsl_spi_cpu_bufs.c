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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int dummy; } ;
struct mpc8xxx_spi {unsigned int count; int /*<<< orphan*/  (* get_tx ) (struct mpc8xxx_spi*) ;struct fsl_spi_reg* reg_base; } ;
struct fsl_spi_reg {int /*<<< orphan*/  transmit; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIM_NE ; 
 int /*<<< orphan*/  mpc8xxx_spi_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mpc8xxx_spi*) ; 

__attribute__((used)) static int fsl_spi_cpu_bufs(struct mpc8xxx_spi *mspi,
				struct spi_transfer *t, unsigned int len)
{
	u32 word;
	struct fsl_spi_reg *reg_base = mspi->reg_base;

	mspi->count = len;

	/* enable rx ints */
	mpc8xxx_spi_write_reg(&reg_base->mask, SPIM_NE);

	/* transmit word */
	word = mspi->get_tx(mspi);
	mpc8xxx_spi_write_reg(&reg_base->transmit, word);

	return 0;
}