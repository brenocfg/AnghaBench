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
 int snd_i2c_bit_ack (struct snd_i2c_bus*) ; 
 int /*<<< orphan*/  snd_i2c_bit_send (struct snd_i2c_bus*,int) ; 

__attribute__((used)) static int snd_i2c_bit_sendbyte(struct snd_i2c_bus *bus, unsigned char data)
{
	int i, err;

	for (i = 7; i >= 0; i--)
		snd_i2c_bit_send(bus, !!(data & (1 << i)));
	err = snd_i2c_bit_ack(bus);
	if (err < 0)
		return err;
	return 0;
}