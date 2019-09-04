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
struct TYPE_2__ {scalar_t__ seqnum; } ;
struct task_struct {TYPE_1__ vmacache; } ;
struct mm_struct {scalar_t__ vmacache_seqnum; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  vmacache_flush (struct task_struct*) ; 
 int /*<<< orphan*/  vmacache_valid_mm (struct mm_struct*) ; 

__attribute__((used)) static bool vmacache_valid(struct mm_struct *mm)
{
	struct task_struct *curr;

	if (!vmacache_valid_mm(mm))
		return false;

	curr = current;
	if (mm->vmacache_seqnum != curr->vmacache.seqnum) {
		/*
		 * First attempt will always be invalid, initialize
		 * the new cache for this task here.
		 */
		curr->vmacache.seqnum = mm->vmacache_seqnum;
		vmacache_flush(curr);
		return false;
	}
	return true;
}