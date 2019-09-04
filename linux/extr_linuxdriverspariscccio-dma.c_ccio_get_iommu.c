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
struct parisc_device {int /*<<< orphan*/  hw_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPHW_IOA ; 
 void* ccio_find_ioc (int /*<<< orphan*/ ) ; 
 struct parisc_device* find_pa_parent_type (struct parisc_device const*,int /*<<< orphan*/ ) ; 

void * ccio_get_iommu(const struct parisc_device *dev)
{
	dev = find_pa_parent_type(dev, HPHW_IOA);
	if (!dev)
		return NULL;

	return ccio_find_ioc(dev->hw_path);
}