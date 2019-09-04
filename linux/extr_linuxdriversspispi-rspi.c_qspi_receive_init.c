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
typedef  int u8 ;
struct rspi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_SPBFCR ; 
 int /*<<< orphan*/  RSPI_SPSR ; 
 int SPBFCR_RXRST ; 
 int SPBFCR_TXRST ; 
 int SPSR_SPRF ; 
 int rspi_read8 (struct rspi_data const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_read_data (struct rspi_data const*) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qspi_receive_init(const struct rspi_data *rspi)
{
	u8 spsr;

	spsr = rspi_read8(rspi, RSPI_SPSR);
	if (spsr & SPSR_SPRF)
		rspi_read_data(rspi);   /* dummy read */
	rspi_write8(rspi, SPBFCR_TXRST | SPBFCR_RXRST, QSPI_SPBFCR);
	rspi_write8(rspi, 0, QSPI_SPBFCR);
}