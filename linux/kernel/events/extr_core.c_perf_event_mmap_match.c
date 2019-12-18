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
struct vm_area_struct {int vm_flags; } ;
struct perf_mmap_event {struct vm_area_struct* vma; } ;
struct TYPE_2__ {scalar_t__ mmap2; scalar_t__ mmap; scalar_t__ mmap_data; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int VM_EXEC ; 

__attribute__((used)) static int perf_event_mmap_match(struct perf_event *event,
				 void *data)
{
	struct perf_mmap_event *mmap_event = data;
	struct vm_area_struct *vma = mmap_event->vma;
	int executable = vma->vm_flags & VM_EXEC;

	return (!executable && event->attr.mmap_data) ||
	       (executable && (event->attr.mmap || event->attr.mmap2));
}