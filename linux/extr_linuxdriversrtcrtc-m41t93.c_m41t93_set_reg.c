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
struct spi_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static inline int m41t93_set_reg(struct spi_device *spi, u8 addr, u8 data)
{
	u8 buf[2];

	/* MSB must be '1' to write */
	buf[0] = addr | 0x80;
	buf[1] = data;

	return spi_write(spi, buf, sizeof(buf));
}