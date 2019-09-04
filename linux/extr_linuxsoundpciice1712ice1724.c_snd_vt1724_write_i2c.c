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
struct snd_ice1712 {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_BYTE_ADDR ; 
 int /*<<< orphan*/  I2C_DATA ; 
 int /*<<< orphan*/  I2C_DEV_ADDR ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char VT1724_I2C_WRITE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_i2c_busy (struct snd_ice1712*) ; 

void snd_vt1724_write_i2c(struct snd_ice1712 *ice,
			  unsigned char dev, unsigned char addr, unsigned char data)
{
	mutex_lock(&ice->i2c_mutex);
	wait_i2c_busy(ice);
	/*
	dev_dbg(ice->card->dev, "i2c_write: [0x%x,0x%x] = 0x%x\n", dev, addr, data);
	*/
	outb(addr, ICEREG1724(ice, I2C_BYTE_ADDR));
	outb(data, ICEREG1724(ice, I2C_DATA));
	outb(dev | VT1724_I2C_WRITE, ICEREG1724(ice, I2C_DEV_ADDR));
	wait_i2c_busy(ice);
	mutex_unlock(&ice->i2c_mutex);
}