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
 int /*<<< orphan*/  STAC9460_I2C_ADDR ; 
 unsigned char snd_vt1724_read_i2c (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned char stac9460_get(struct snd_ice1712 *ice, int reg)
{
	return snd_vt1724_read_i2c(ice, STAC9460_I2C_ADDR, reg);
}