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
struct vm_area_struct {TYPE_1__* vm_region; int /*<<< orphan*/  vm_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_top; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSYS ; 
 int call_mmap (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int do_mmap_shared_file(struct vm_area_struct *vma)
{
	int ret;

	ret = call_mmap(vma->vm_file, vma);
	if (ret == 0) {
		vma->vm_region->vm_top = vma->vm_region->vm_end;
		return 0;
	}
	if (ret != -ENOSYS)
		return ret;

	/* getting -ENOSYS indicates that direct mmap isn't possible (as
	 * opposed to tried but failed) so we can only give a suitable error as
	 * it's not possible to make a private copy if MAP_SHARED was given */
	return -ENODEV;
}