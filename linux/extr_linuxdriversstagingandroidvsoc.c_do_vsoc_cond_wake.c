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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct vsoc_region_data {int /*<<< orphan*/  futex_wait_queue; } ;
struct vsoc_device_region {scalar_t__ region_begin_offset; scalar_t__ region_end_offset; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct vsoc_region_data* regions_data; } ;

/* Variables and functions */
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int iminor (int /*<<< orphan*/ ) ; 
 TYPE_1__ vsoc_dev ; 
 struct vsoc_device_region* vsoc_region_from_filep (struct file*) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_vsoc_cond_wake(struct file *filp, uint32_t offset)
{
	struct vsoc_device_region *region_p = vsoc_region_from_filep(filp);
	u32 region_number = iminor(file_inode(filp));
	struct vsoc_region_data *data = vsoc_dev.regions_data + region_number;
	/* Ensure that the offset is aligned */
	if (offset & (sizeof(uint32_t) - 1))
		return -EADDRNOTAVAIL;
	/* Ensure that the offset is within shared memory */
	if (((uint64_t)offset) + region_p->region_begin_offset +
	    sizeof(uint32_t) > region_p->region_end_offset)
		return -E2BIG;
	/*
	 * TODO(b/73664181): Use multiple futex wait queues.
	 * We need to wake every sleeper when the condition changes. Typically
	 * only a single thread will be waiting on the condition, but there
	 * are exceptions. The worst case is about 10 threads.
	 */
	wake_up_interruptible_all(&data->futex_wait_queue);
	return 0;
}