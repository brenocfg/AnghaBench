#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  vm_mm; scalar_t__ vm_pgoff; TYPE_2__* vm_file; } ;
struct perf_event {TYPE_1__* pmu; TYPE_3__* rb; int /*<<< orphan*/  mmap_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  aux_mmap_count; int /*<<< orphan*/  mmap_count; } ;
struct TYPE_5__ {struct perf_event* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_mapped ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_mmap_open(struct vm_area_struct *vma)
{
	struct perf_event *event = vma->vm_file->private_data;

	atomic_inc(&event->mmap_count);
	atomic_inc(&event->rb->mmap_count);

	if (vma->vm_pgoff)
		atomic_inc(&event->rb->aux_mmap_count);

	if (event->pmu->event_mapped)
		event->pmu->event_mapped(event, vma->vm_mm);
}