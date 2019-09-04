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
typedef  int u32 ;
struct bcm_qspi {int bspi_maj_rev; int bspi_min_rev; int bspi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI ; 
 int /*<<< orphan*/  BSPI_B0_CTRL ; 
 int /*<<< orphan*/  BSPI_B1_CTRL ; 
 int /*<<< orphan*/  BSPI_BSPI_XOR_ENABLE ; 
 int /*<<< orphan*/  BSPI_BSPI_XOR_VALUE ; 
 int /*<<< orphan*/  BSPI_REVISION_ID ; 
 int /*<<< orphan*/  bcm_qspi_bspi_ver_three (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_disable_bspi (struct bcm_qspi*) ; 
 int bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm_qspi_bspi_init(struct bcm_qspi *qspi)
{
	u32 val = 0;

	val = bcm_qspi_read(qspi, BSPI, BSPI_REVISION_ID);
	qspi->bspi_maj_rev = (val >> 8) & 0xff;
	qspi->bspi_min_rev = val & 0xff;
	if (!(bcm_qspi_bspi_ver_three(qspi))) {
		/* Force mapping of BSPI address -> flash offset */
		bcm_qspi_write(qspi, BSPI, BSPI_BSPI_XOR_VALUE, 0);
		bcm_qspi_write(qspi, BSPI, BSPI_BSPI_XOR_ENABLE, 1);
	}
	qspi->bspi_enabled = 1;
	bcm_qspi_disable_bspi(qspi);
	bcm_qspi_write(qspi, BSPI, BSPI_B0_CTRL, 0);
	bcm_qspi_write(qspi, BSPI, BSPI_B1_CTRL, 0);
}