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
struct snd_ice1712 {int /*<<< orphan*/  i2c; int /*<<< orphan*/  cs8427; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int snd_i2c_readbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int snd_i2c_sendbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ice1712_cs8427_set_input_clock(struct snd_ice1712 *ice, int spdif_clock)
{
	unsigned char reg[2] = { 0x80 | 4, 0 };   /* CS8427 auto increment | register number 4 + data */
	unsigned char val, nval;
	int res = 0;

	snd_i2c_lock(ice->i2c);
	if (snd_i2c_sendbytes(ice->cs8427, reg, 1) != 1) {
		snd_i2c_unlock(ice->i2c);
		return -EIO;
	}
	if (snd_i2c_readbytes(ice->cs8427, &val, 1) != 1) {
		snd_i2c_unlock(ice->i2c);
		return -EIO;
	}
	nval = val & 0xf0;
	if (spdif_clock)
		nval |= 0x01;
	else
		nval |= 0x04;
	if (val != nval) {
		reg[1] = nval;
		if (snd_i2c_sendbytes(ice->cs8427, reg, 2) != 2) {
			res = -EIO;
		} else {
			res++;
		}
	}
	snd_i2c_unlock(ice->i2c);
	return res;
}