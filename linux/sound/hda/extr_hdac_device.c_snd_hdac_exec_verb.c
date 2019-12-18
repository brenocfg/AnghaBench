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
struct hdac_device {int (* exec_verb ) (struct hdac_device*,unsigned int,unsigned int,unsigned int*) ;int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int snd_hdac_bus_exec_verb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int stub1 (struct hdac_device*,unsigned int,unsigned int,unsigned int*) ; 

int snd_hdac_exec_verb(struct hdac_device *codec, unsigned int cmd,
		       unsigned int flags, unsigned int *res)
{
	if (codec->exec_verb)
		return codec->exec_verb(codec, cmd, flags, res);
	return snd_hdac_bus_exec_verb(codec->bus, codec->addr, cmd, res);
}