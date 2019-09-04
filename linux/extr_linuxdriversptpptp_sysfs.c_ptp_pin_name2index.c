#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptp_clock {TYPE_2__* info; } ;
struct TYPE_4__ {int n_pins; TYPE_1__* pin_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int ptp_pin_name2index(struct ptp_clock *ptp, const char *name)
{
	int i;
	for (i = 0; i < ptp->info->n_pins; i++) {
		if (!strcmp(ptp->info->pin_config[i].name, name))
			return i;
	}
	return -1;
}