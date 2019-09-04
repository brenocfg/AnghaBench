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
struct s6e63m0 {int dummy; } ;

/* Variables and functions */
 unsigned char COMMAND_ONLY ; 
 unsigned char DATA_ONLY ; 
 int s6e63m0_spi_write_byte (struct s6e63m0*,int,unsigned char) ; 

__attribute__((used)) static int s6e63m0_spi_write(struct s6e63m0 *lcd, unsigned char address,
	unsigned char command)
{
	int ret = 0;

	if (address != DATA_ONLY)
		ret = s6e63m0_spi_write_byte(lcd, 0x0, address);
	if (command != COMMAND_ONLY)
		ret = s6e63m0_spi_write_byte(lcd, 0x1, command);

	return ret;
}