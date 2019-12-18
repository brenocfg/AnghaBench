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
struct snd_soc_component {int dummy; } ;
struct cx20442_priv {unsigned int reg_cache; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
 struct cx20442_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static unsigned int cx20442_read_reg_cache(struct snd_soc_component *component,
					   unsigned int reg)
{
	struct cx20442_priv *cx20442 = snd_soc_component_get_drvdata(component);

	if (reg >= 1)
		return -EINVAL;

	return cx20442->reg_cache;
}