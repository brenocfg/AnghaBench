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
struct lms501kf03 {int dummy; } ;

/* Variables and functions */
 int lms501kf03_spi_write_byte (struct lms501kf03*,unsigned char,unsigned char) ; 

__attribute__((used)) static int lms501kf03_spi_write(struct lms501kf03 *lcd, unsigned char address,
				unsigned char command)
{
	return lms501kf03_spi_write_byte(lcd, address, command);
}