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
struct TYPE_2__ {int /*<<< orphan*/  (* suspend ) (struct snd_soc_dai*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_soc_dai*) ; 

void snd_soc_dai_suspend(struct snd_soc_dai *dai)
{
	if (dai->driver->suspend)
		dai->driver->suspend(dai);
}