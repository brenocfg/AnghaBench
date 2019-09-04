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
 int ENXIO ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int dimm_name_to_id(struct device *dev)
{
	int dimm;

	if (sscanf(dev_name(dev), "test_dimm%d", &dimm) != 1)
		return -ENXIO;
	return dimm;
}