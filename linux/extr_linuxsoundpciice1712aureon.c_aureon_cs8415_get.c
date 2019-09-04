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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUREON_CS8415_CS ; 
 int /*<<< orphan*/  aureon_spi_read (struct snd_ice1712*,int /*<<< orphan*/ ,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  aureon_spi_write (struct snd_ice1712*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned char aureon_cs8415_get(struct snd_ice1712 *ice, int reg)
{
	unsigned char val;
	aureon_spi_write(ice, AUREON_CS8415_CS, 0x2000 | reg, 16);
	aureon_spi_read(ice, AUREON_CS8415_CS, 0x21, 8, &val, 1);
	return val;
}