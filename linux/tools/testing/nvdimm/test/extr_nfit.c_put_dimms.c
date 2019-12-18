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
struct nfit_test {int num_dcr; scalar_t__* dimm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (scalar_t__) ; 

__attribute__((used)) static void put_dimms(void *data)
{
	struct nfit_test *t = data;
	int i;

	for (i = 0; i < t->num_dcr; i++)
		if (t->dimm_dev[i])
			device_unregister(t->dimm_dev[i]);
}