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
struct ams369fg06 {int dummy; } ;

/* Variables and functions */
 unsigned char COMMAND_ONLY ; 
 unsigned char DATA_ONLY ; 
 int ams369fg06_spi_write_byte (struct ams369fg06*,int,unsigned char) ; 

__attribute__((used)) static int ams369fg06_spi_write(struct ams369fg06 *lcd, unsigned char address,
	unsigned char command)
{
	int ret = 0;

	if (address != DATA_ONLY)
		ret = ams369fg06_spi_write_byte(lcd, 0x70, address);
	if (command != COMMAND_ONLY)
		ret = ams369fg06_spi_write_byte(lcd, 0x72, command);

	return ret;
}