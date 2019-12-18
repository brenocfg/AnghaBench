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
struct snd_soc_component {scalar_t__ suspended; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct snd_soc_component*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_soc_component*) ; 

void snd_soc_component_resume(struct snd_soc_component *component)
{
	if (component->driver->resume)
		component->driver->resume(component);
	component->suspended = 0;
}