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
struct intel_padgroup {unsigned int base; unsigned int size; } ;
struct intel_community {int ngpps; struct intel_padgroup* gpps; } ;

/* Variables and functions */

__attribute__((used)) static const struct intel_padgroup *
intel_community_get_padgroup(const struct intel_community *community,
			     unsigned pin)
{
	int i;

	for (i = 0; i < community->ngpps; i++) {
		const struct intel_padgroup *padgrp = &community->gpps[i];

		if (pin >= padgrp->base && pin < padgrp->base + padgrp->size)
			return padgrp;
	}

	return NULL;
}