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
 int AK4114_ADDR ; 
 int /*<<< orphan*/  ap192_4wire_finish (struct snd_ice1712*,unsigned int) ; 
 unsigned int ap192_4wire_start (struct snd_ice1712*) ; 
 int /*<<< orphan*/  write_data (struct snd_ice1712*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void ap192_ak4114_write(void *private_data, unsigned char addr,
			       unsigned char data)
{
	struct snd_ice1712 *ice = private_data;
	unsigned int tmp, addrdata;

	tmp = ap192_4wire_start(ice);
	addrdata = (AK4114_ADDR << 6) | 0x20 | (addr & 0x1f);
	addrdata = (addrdata << 8) | data;
	write_data(ice, tmp, addrdata, 15);
	ap192_4wire_finish(ice, tmp);
}