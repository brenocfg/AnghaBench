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
struct snd_soc_dai {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* remove ) (struct snd_soc_dai*) ;} ;

/* Variables and functions */
 int stub1 (struct snd_soc_dai*) ; 

int snd_soc_dai_remove(struct snd_soc_dai *dai)
{
	if (dai->driver->remove)
		return dai->driver->remove(dai);
	return 0;
}