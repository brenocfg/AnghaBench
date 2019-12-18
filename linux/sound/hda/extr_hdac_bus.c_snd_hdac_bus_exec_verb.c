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
struct hdac_bus {int /*<<< orphan*/  cmd_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_hdac_bus_exec_verb_unlocked (struct hdac_bus*,unsigned int,unsigned int,unsigned int*) ; 

int snd_hdac_bus_exec_verb(struct hdac_bus *bus, unsigned int addr,
			   unsigned int cmd, unsigned int *res)
{
	int err;

	mutex_lock(&bus->cmd_mutex);
	err = snd_hdac_bus_exec_verb_unlocked(bus, addr, cmd, res);
	mutex_unlock(&bus->cmd_mutex);
	return err;
}