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
struct snd_i2c_bus {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int snd_i2c_bit_sendbyte (struct snd_i2c_bus*,unsigned short) ; 
 int /*<<< orphan*/  snd_i2c_bit_start (struct snd_i2c_bus*) ; 
 int /*<<< orphan*/  snd_i2c_bit_stop (struct snd_i2c_bus*) ; 

__attribute__((used)) static int snd_i2c_bit_probeaddr(struct snd_i2c_bus *bus, unsigned short addr)
{
	int err;

	if (addr & 0x8000)	/* 10-bit address */
		return -EIO;	/* not yet implemented */
	if (addr & 0x7f80)	/* invalid address */
		return -EINVAL;
	snd_i2c_bit_start(bus);
	err = snd_i2c_bit_sendbyte(bus, addr << 1);
	snd_i2c_bit_stop(bus);
	return err;
}