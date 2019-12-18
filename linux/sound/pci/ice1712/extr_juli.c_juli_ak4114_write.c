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
 int /*<<< orphan*/  AK4114_ADDR ; 
 int /*<<< orphan*/  snd_vt1724_write_i2c (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void juli_ak4114_write(void *private_data, unsigned char reg,
				unsigned char val)
{
	snd_vt1724_write_i2c((struct snd_ice1712 *)private_data, AK4114_ADDR,
				reg, val);
}