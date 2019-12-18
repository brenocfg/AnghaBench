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
 scalar_t__ snd_i2c_bit_data (struct snd_i2c_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_i2c_bit_direction (struct snd_i2c_bus*,int,int) ; 
 int /*<<< orphan*/  snd_i2c_bit_send (struct snd_i2c_bus*,int) ; 
 int /*<<< orphan*/  snd_i2c_bit_set (struct snd_i2c_bus*,int,int) ; 

__attribute__((used)) static int snd_i2c_bit_readbyte(struct snd_i2c_bus *bus, int last)
{
	int i;
	unsigned char data = 0;

	snd_i2c_bit_set(bus, 0, 1);
	snd_i2c_bit_direction(bus, 1, 0);	/* SCL - wr, SDA - rd */
	for (i = 7; i >= 0; i--) {
		snd_i2c_bit_set(bus, 1, 1);
		if (snd_i2c_bit_data(bus, 0))
			data |= (1 << i);
		snd_i2c_bit_set(bus, 0, 1);
	}
	snd_i2c_bit_direction(bus, 1, 1);	/* SCL - wr, SDA - wr */
	snd_i2c_bit_send(bus, !!last);
	return data;
}