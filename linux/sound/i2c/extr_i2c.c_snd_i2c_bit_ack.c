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
 int EIO ; 
 int snd_i2c_bit_data (struct snd_i2c_bus*,int) ; 
 int /*<<< orphan*/  snd_i2c_bit_direction (struct snd_i2c_bus*,int,int) ; 
 int /*<<< orphan*/  snd_i2c_bit_set (struct snd_i2c_bus*,int,int) ; 

__attribute__((used)) static int snd_i2c_bit_ack(struct snd_i2c_bus *bus)
{
	int ack;

	snd_i2c_bit_set(bus, 0, 1);
	snd_i2c_bit_set(bus, 1, 1);
	snd_i2c_bit_direction(bus, 1, 0);	/* SCL - wr, SDA - rd */
	ack = snd_i2c_bit_data(bus, 1);
	snd_i2c_bit_direction(bus, 1, 1);	/* SCL - wr, SDA - wr */
	snd_i2c_bit_set(bus, 0, 1);
	return ack ? -EIO : 0;
}