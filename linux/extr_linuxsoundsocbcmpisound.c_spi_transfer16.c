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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  txbuf ;

/* Variables and functions */
 int /*<<< orphan*/  pisnd_spi_device ; 
 int /*<<< orphan*/  printd (char*,int,int) ; 
 int /*<<< orphan*/  printe (char*) ; 
 int /*<<< orphan*/  spi_transfer (int*,int*,int) ; 

__attribute__((used)) static uint16_t spi_transfer16(uint16_t val)
{
	uint8_t txbuf[2];
	uint8_t rxbuf[2];

	if (!pisnd_spi_device) {
		printe("pisnd_spi_device null, returning\n");
		return 0;
	}

	txbuf[0] = val >> 8;
	txbuf[1] = val & 0xff;

	spi_transfer(txbuf, rxbuf, sizeof(txbuf));

	printd("received: %02x%02x\n", rxbuf[0], rxbuf[1]);

	return (rxbuf[0] << 8) | rxbuf[1];
}