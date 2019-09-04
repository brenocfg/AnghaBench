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
struct spi_device {int /*<<< orphan*/  master; } ;
struct a3700_spi {unsigned int wait_mask; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_IF_CTRL_REG ; 
 int /*<<< orphan*/  A3700_SPI_INT_MASK_REG ; 
 int /*<<< orphan*/  A3700_SPI_TIMEOUT ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct a3700_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 unsigned int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool a3700_spi_wait_completion(struct spi_device *spi)
{
	struct a3700_spi *a3700_spi;
	unsigned int timeout;
	unsigned int ctrl_reg;
	unsigned long timeout_jiffies;

	a3700_spi = spi_master_get_devdata(spi->master);

	/* SPI interrupt is edge-triggered, which means an interrupt will
	 * be generated only when detecting a specific status bit changed
	 * from '0' to '1'. So when we start waiting for a interrupt, we
	 * need to check status bit in control reg first, if it is already 1,
	 * then we do not need to wait for interrupt
	 */
	ctrl_reg = spireg_read(a3700_spi, A3700_SPI_IF_CTRL_REG);
	if (a3700_spi->wait_mask & ctrl_reg)
		return true;

	reinit_completion(&a3700_spi->done);

	spireg_write(a3700_spi, A3700_SPI_INT_MASK_REG,
		     a3700_spi->wait_mask);

	timeout_jiffies = msecs_to_jiffies(A3700_SPI_TIMEOUT);
	timeout = wait_for_completion_timeout(&a3700_spi->done,
					      timeout_jiffies);

	a3700_spi->wait_mask = 0;

	if (timeout)
		return true;

	/* there might be the case that right after we checked the
	 * status bits in this routine and before start to wait for
	 * interrupt by wait_for_completion_timeout, the interrupt
	 * happens, to avoid missing it we need to double check
	 * status bits in control reg, if it is already 1, then
	 * consider that we have the interrupt successfully and
	 * return true.
	 */
	ctrl_reg = spireg_read(a3700_spi, A3700_SPI_IF_CTRL_REG);
	if (a3700_spi->wait_mask & ctrl_reg)
		return true;

	spireg_write(a3700_spi, A3700_SPI_INT_MASK_REG, 0);

	/* Timeout was reached */
	return false;
}