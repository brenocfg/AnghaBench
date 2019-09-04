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
struct ocfs2_per_slot_free_list {int /*<<< orphan*/  f_first; } ;
struct ocfs2_extent_tree {TYPE_1__* et_dealloc; } ;
struct TYPE_2__ {struct ocfs2_per_slot_free_list* c_first_suballocator; } ;

/* Variables and functions */

__attribute__((used)) static int ocfs2_is_dealloc_empty(struct ocfs2_extent_tree *et)
{
	struct ocfs2_per_slot_free_list *fl = NULL;

	if (!et->et_dealloc)
		return 1;

	fl = et->et_dealloc->c_first_suballocator;
	if (!fl)
		return 1;

	if (!fl->f_first)
		return 1;

	return 0;
}