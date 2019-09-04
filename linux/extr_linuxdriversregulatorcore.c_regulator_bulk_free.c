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
struct regulator_bulk_data {int /*<<< orphan*/ * consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ *) ; 

void regulator_bulk_free(int num_consumers,
			 struct regulator_bulk_data *consumers)
{
	int i;

	for (i = 0; i < num_consumers; i++) {
		regulator_put(consumers[i].consumer);
		consumers[i].consumer = NULL;
	}
}