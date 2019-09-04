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
 int ENOENT ; 

__attribute__((used)) static int ap_cs8427_probeaddr(struct snd_i2c_bus *bus, unsigned short addr)
{
	if (addr == 0x10)
		return 1;
	return -ENOENT;
}