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
struct xol_area {struct xol_area* bitmap; int /*<<< orphan*/ * pages; } ;
struct TYPE_2__ {struct xol_area* xol_area; } ;
struct mm_struct {TYPE_1__ uprobes_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_uprobe_lock ; 
 int /*<<< orphan*/  delayed_uprobe_remove (int /*<<< orphan*/ *,struct mm_struct*) ; 
 int /*<<< orphan*/  kfree (struct xol_area*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

void uprobe_clear_state(struct mm_struct *mm)
{
	struct xol_area *area = mm->uprobes_state.xol_area;

	mutex_lock(&delayed_uprobe_lock);
	delayed_uprobe_remove(NULL, mm);
	mutex_unlock(&delayed_uprobe_lock);

	if (!area)
		return;

	put_page(area->pages[0]);
	kfree(area->bitmap);
	kfree(area);
}