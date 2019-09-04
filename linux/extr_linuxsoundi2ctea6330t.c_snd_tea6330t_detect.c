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
 int /*<<< orphan*/  TEA6330T_ADDR ; 
 int /*<<< orphan*/  snd_i2c_lock (struct snd_i2c_bus*) ; 
 int snd_i2c_probeaddr (struct snd_i2c_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_i2c_unlock (struct snd_i2c_bus*) ; 

int snd_tea6330t_detect(struct snd_i2c_bus *bus, int equalizer)
{
	int res;

	snd_i2c_lock(bus);
	res = snd_i2c_probeaddr(bus, TEA6330T_ADDR);
	snd_i2c_unlock(bus);
	return res;
}