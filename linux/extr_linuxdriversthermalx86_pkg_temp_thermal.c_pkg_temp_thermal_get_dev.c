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
struct pkg_device {int dummy; } ;

/* Variables and functions */
 int max_packages ; 
 struct pkg_device** packages ; 
 int topology_logical_package_id (unsigned int) ; 

__attribute__((used)) static struct pkg_device *pkg_temp_thermal_get_dev(unsigned int cpu)
{
	int pkgid = topology_logical_package_id(cpu);

	if (pkgid >= 0 && pkgid < max_packages)
		return packages[pkgid];
	return NULL;
}