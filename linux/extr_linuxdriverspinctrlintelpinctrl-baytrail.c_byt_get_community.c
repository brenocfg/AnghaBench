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
struct byt_gpio {struct byt_community* communities_copy; TYPE_1__* soc_data; } ;
struct byt_community {unsigned int pin_base; unsigned int npins; } ;
struct TYPE_2__ {int ncommunities; } ;

/* Variables and functions */

__attribute__((used)) static struct byt_community *byt_get_community(struct byt_gpio *vg,
					       unsigned int pin)
{
	struct byt_community *comm;
	int i;

	for (i = 0; i < vg->soc_data->ncommunities; i++) {
		comm = vg->communities_copy + i;
		if (pin < comm->pin_base + comm->npins && pin >= comm->pin_base)
			return comm;
	}

	return NULL;
}