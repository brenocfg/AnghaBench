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
typedef  int /*<<< orphan*/  uprobe_opcode_t ;
struct TYPE_3__ {char* name; int /*<<< orphan*/ ** pages; int /*<<< orphan*/ * fault; } ;
struct xol_area {unsigned long vaddr; struct xol_area* bitmap; int /*<<< orphan*/ ** pages; int /*<<< orphan*/  slot_count; int /*<<< orphan*/  wq; TYPE_1__ xol_mapping; } ;
struct mm_struct {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UINSNS_PER_PAGE ; 
 int /*<<< orphan*/  UPROBE_SWBP_INSN ; 
 int /*<<< orphan*/  UPROBE_SWBP_INSN_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_uprobe_copy_ixol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct xol_area* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xol_area*) ; 
 struct xol_area* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,struct xol_area*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xol_add_vma (struct mm_struct*,struct xol_area*) ; 

__attribute__((used)) static struct xol_area *__create_xol_area(unsigned long vaddr)
{
	struct mm_struct *mm = current->mm;
	uprobe_opcode_t insn = UPROBE_SWBP_INSN;
	struct xol_area *area;

	area = kmalloc(sizeof(*area), GFP_KERNEL);
	if (unlikely(!area))
		goto out;

	area->bitmap = kcalloc(BITS_TO_LONGS(UINSNS_PER_PAGE), sizeof(long),
			       GFP_KERNEL);
	if (!area->bitmap)
		goto free_area;

	area->xol_mapping.name = "[uprobes]";
	area->xol_mapping.fault = NULL;
	area->xol_mapping.pages = area->pages;
	area->pages[0] = alloc_page(GFP_HIGHUSER);
	if (!area->pages[0])
		goto free_bitmap;
	area->pages[1] = NULL;

	area->vaddr = vaddr;
	init_waitqueue_head(&area->wq);
	/* Reserve the 1st slot for get_trampoline_vaddr() */
	set_bit(0, area->bitmap);
	atomic_set(&area->slot_count, 1);
	arch_uprobe_copy_ixol(area->pages[0], 0, &insn, UPROBE_SWBP_INSN_SIZE);

	if (!xol_add_vma(mm, area))
		return area;

	__free_page(area->pages[0]);
 free_bitmap:
	kfree(area->bitmap);
 free_area:
	kfree(area);
 out:
	return NULL;
}