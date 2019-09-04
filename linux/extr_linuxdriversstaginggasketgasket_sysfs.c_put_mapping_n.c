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
struct gasket_sysfs_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_mapping (struct gasket_sysfs_mapping*) ; 

__attribute__((used)) static void put_mapping_n(struct gasket_sysfs_mapping *mapping, int times)
{
	int i;

	for (i = 0; i < times; i++)
		put_mapping(mapping);
}