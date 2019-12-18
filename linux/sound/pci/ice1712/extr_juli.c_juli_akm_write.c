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
struct snd_akm4xxx {struct snd_ice1712** private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4358_ADDR ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_vt1724_write_i2c (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void juli_akm_write(struct snd_akm4xxx *ak, int chip,
			   unsigned char addr, unsigned char data)
{
	struct snd_ice1712 *ice = ak->private_data[0];
	 
	if (snd_BUG_ON(chip))
		return;
	snd_vt1724_write_i2c(ice, AK4358_ADDR, addr, data);
}