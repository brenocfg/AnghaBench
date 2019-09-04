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
struct intel_pinctrl {int ncommunities; struct intel_community* communities; } ;
struct intel_padgroup {unsigned int gpio_base; unsigned int size; } ;
struct intel_community {int ngpps; struct intel_padgroup* gpps; } ;

/* Variables and functions */

__attribute__((used)) static unsigned intel_gpio_ngpio(const struct intel_pinctrl *pctrl)
{
	const struct intel_community *community;
	unsigned ngpio = 0;
	int i, j;

	for (i = 0; i < pctrl->ncommunities; i++) {
		community = &pctrl->communities[i];
		for (j = 0; j < community->ngpps; j++) {
			const struct intel_padgroup *gpp = &community->gpps[j];

			if (gpp->gpio_base < 0)
				continue;

			if (gpp->gpio_base + gpp->size > ngpio)
				ngpio = gpp->gpio_base + gpp->size;
		}
	}

	return ngpio;
}