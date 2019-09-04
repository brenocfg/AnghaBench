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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_PACKETCONFIG1_CRC_ON ; 
 int /*<<< orphan*/  REG_PACKETCONFIG1 ; 
 int rf69_set_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_enable_crc(struct spi_device *spi)
{
	return rf69_set_bit(spi, REG_PACKETCONFIG1, MASK_PACKETCONFIG1_CRC_ON);
}