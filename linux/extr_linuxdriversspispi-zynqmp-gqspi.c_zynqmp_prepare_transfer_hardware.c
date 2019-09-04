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
struct zynqmp_qspi {int dummy; } ;
struct spi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GQSPI_EN_MASK ; 
 int /*<<< orphan*/  GQSPI_EN_OFST ; 
 struct zynqmp_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zynqmp_prepare_transfer_hardware(struct spi_master *master)
{
	struct zynqmp_qspi *xqspi = spi_master_get_devdata(master);

	zynqmp_gqspi_write(xqspi, GQSPI_EN_OFST, GQSPI_EN_MASK);
	return 0;
}