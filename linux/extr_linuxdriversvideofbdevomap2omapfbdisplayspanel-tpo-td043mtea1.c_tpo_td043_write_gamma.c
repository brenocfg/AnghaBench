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
typedef  int u16 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpo_td043_write (struct spi_device*,int,int) ; 

__attribute__((used)) static void tpo_td043_write_gamma(struct spi_device *spi, u16 gamma[12])
{
	u8 i, val;

	/* gamma bits [9:8] */
	for (val = i = 0; i < 4; i++)
		val |= (gamma[i] & 0x300) >> ((i + 1) * 2);
	tpo_td043_write(spi, 0x11, val);

	for (val = i = 0; i < 4; i++)
		val |= (gamma[i+4] & 0x300) >> ((i + 1) * 2);
	tpo_td043_write(spi, 0x12, val);

	for (val = i = 0; i < 4; i++)
		val |= (gamma[i+8] & 0x300) >> ((i + 1) * 2);
	tpo_td043_write(spi, 0x13, val);

	/* gamma bits [7:0] */
	for (val = i = 0; i < 12; i++)
		tpo_td043_write(spi, 0x14 + i, gamma[i] & 0xff);
}