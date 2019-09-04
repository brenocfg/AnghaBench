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
struct xol_area {int /*<<< orphan*/ * pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  ixol; } ;
struct uprobe {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_uprobe_copy_ixol (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int) ; 
 struct xol_area* get_xol_area () ; 
 scalar_t__ unlikely (int) ; 
 unsigned long xol_take_insn_slot (struct xol_area*) ; 

__attribute__((used)) static unsigned long xol_get_insn_slot(struct uprobe *uprobe)
{
	struct xol_area *area;
	unsigned long xol_vaddr;

	area = get_xol_area();
	if (!area)
		return 0;

	xol_vaddr = xol_take_insn_slot(area);
	if (unlikely(!xol_vaddr))
		return 0;

	arch_uprobe_copy_ixol(area->pages[0], xol_vaddr,
			      &uprobe->arch.ixol, sizeof(uprobe->arch.ixol));

	return xol_vaddr;
}