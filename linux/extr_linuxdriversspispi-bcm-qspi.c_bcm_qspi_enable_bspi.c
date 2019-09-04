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
struct bcm_qspi {int bspi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI ; 
 int /*<<< orphan*/  BSPI_MAST_N_BOOT_CTRL ; 
 int /*<<< orphan*/  bcm_qspi_bspi_flush_prefetch_buffers (struct bcm_qspi*) ; 
 int bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_bspi (struct bcm_qspi*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcm_qspi_enable_bspi(struct bcm_qspi *qspi)
{
	if (!has_bspi(qspi))
		return;

	qspi->bspi_enabled = 1;
	if ((bcm_qspi_read(qspi, BSPI, BSPI_MAST_N_BOOT_CTRL) & 1) == 0)
		return;

	bcm_qspi_bspi_flush_prefetch_buffers(qspi);
	udelay(1);
	bcm_qspi_write(qspi, BSPI, BSPI_MAST_N_BOOT_CTRL, 0);
	udelay(1);
}