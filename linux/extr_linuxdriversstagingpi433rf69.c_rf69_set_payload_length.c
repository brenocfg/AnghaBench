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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PAYLOAD_LENGTH ; 
 int rf69_write_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_payload_length(struct spi_device *spi, u8 payload_length)
{
	return rf69_write_reg(spi, REG_PAYLOAD_LENGTH, payload_length);
}