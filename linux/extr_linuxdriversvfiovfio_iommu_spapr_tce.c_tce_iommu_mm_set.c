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
struct tce_container {TYPE_1__* mm; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 long EPERM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 

__attribute__((used)) static long tce_iommu_mm_set(struct tce_container *container)
{
	if (container->mm) {
		if (container->mm == current->mm)
			return 0;
		return -EPERM;
	}
	BUG_ON(!current->mm);
	container->mm = current->mm;
	atomic_inc(&container->mm->mm_count);

	return 0;
}