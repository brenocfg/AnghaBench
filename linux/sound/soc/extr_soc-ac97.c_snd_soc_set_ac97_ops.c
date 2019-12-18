#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97_bus_ops {int dummy; } ;
struct TYPE_2__ {struct snd_ac97_bus_ops* ops; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__ soc_ac97_bus ; 
 struct snd_ac97_bus_ops* soc_ac97_ops ; 

int snd_soc_set_ac97_ops(struct snd_ac97_bus_ops *ops)
{
	if (ops == soc_ac97_ops)
		return 0;

	if (soc_ac97_ops && ops)
		return -EBUSY;

	soc_ac97_ops = ops;
	soc_ac97_bus.ops = ops;

	return 0;
}