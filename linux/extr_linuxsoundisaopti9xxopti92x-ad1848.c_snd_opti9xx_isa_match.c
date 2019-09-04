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
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int snd_opti9xx_isa_match(struct device *devptr,
				 unsigned int dev)
{
#ifdef CONFIG_PNP
	if (snd_opti9xx_pnp_is_probed)
		return 0;
	if (isapnp)
		return 0;
#endif
	return 1;
}