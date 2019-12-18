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
struct dsa_tag_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_tag_driver_unregister (struct dsa_tag_driver*) ; 

void dsa_tag_drivers_unregister(struct dsa_tag_driver *dsa_tag_driver_array[],
				unsigned int count)
{
	unsigned int i;

	for (i = 0; i < count; i++)
		dsa_tag_driver_unregister(dsa_tag_driver_array[i]);
}