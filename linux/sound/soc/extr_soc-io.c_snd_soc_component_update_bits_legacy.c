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
struct snd_soc_component {int /*<<< orphan*/  io_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_soc_component_read (struct snd_soc_component*,unsigned int,unsigned int*) ; 
 int snd_soc_component_write (struct snd_soc_component*,unsigned int,unsigned int) ; 

__attribute__((used)) static int snd_soc_component_update_bits_legacy(
	struct snd_soc_component *component, unsigned int reg,
	unsigned int mask, unsigned int val, bool *change)
{
	unsigned int old, new;
	int ret;

	mutex_lock(&component->io_mutex);

	ret = snd_soc_component_read(component, reg, &old);
	if (ret < 0)
		goto out_unlock;

	new = (old & ~mask) | (val & mask);
	*change = old != new;
	if (*change)
		ret = snd_soc_component_write(component, reg, new);
out_unlock:
	mutex_unlock(&component->io_mutex);

	return ret;
}