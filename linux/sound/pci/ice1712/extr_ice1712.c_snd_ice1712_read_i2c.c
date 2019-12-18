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
 int /*<<< orphan*/  I2C_BYTE_ADDR ; 
 int /*<<< orphan*/  I2C_CTRL ; 
 int /*<<< orphan*/  I2C_DATA ; 
 int /*<<< orphan*/  I2C_DEV_ADDR ; 
 unsigned char ICE1712_I2C_BUSY ; 
 unsigned char ICE1712_I2C_WRITE ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char snd_ice1712_read_i2c(struct snd_ice1712 *ice,
					  unsigned char dev,
					  unsigned char addr)
{
	long t = 0x10000;

	outb(addr, ICEREG(ice, I2C_BYTE_ADDR));
	outb(dev & ~ICE1712_I2C_WRITE, ICEREG(ice, I2C_DEV_ADDR));
	while (t-- > 0 && (inb(ICEREG(ice, I2C_CTRL)) & ICE1712_I2C_BUSY)) ;
	return inb(ICEREG(ice, I2C_DATA));
}