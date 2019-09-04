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
struct zynqmp_qspi {int bytes_to_transfer; int txbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GQSPI_TXD_OFST ; 
 int /*<<< orphan*/  memcpy (int*,int,int) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zynqmp_qspi_filltxfifo(struct zynqmp_qspi *xqspi, int size)
{
	u32 count = 0, intermediate;

	while ((xqspi->bytes_to_transfer > 0) && (count < size)) {
		memcpy(&intermediate, xqspi->txbuf, 4);
		zynqmp_gqspi_write(xqspi, GQSPI_TXD_OFST, intermediate);

		if (xqspi->bytes_to_transfer >= 4) {
			xqspi->txbuf += 4;
			xqspi->bytes_to_transfer -= 4;
		} else {
			xqspi->txbuf += xqspi->bytes_to_transfer;
			xqspi->bytes_to_transfer = 0;
		}
		count++;
	}
}