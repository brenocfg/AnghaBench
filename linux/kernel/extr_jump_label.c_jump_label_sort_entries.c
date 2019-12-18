#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct jump_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HAVE_ARCH_JUMP_LABEL_RELATIVE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_label_cmp ; 
 void* jump_label_swap ; 
 int /*<<< orphan*/  sort (struct jump_entry*,unsigned long,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
jump_label_sort_entries(struct jump_entry *start, struct jump_entry *stop)
{
	unsigned long size;
	void *swapfn = NULL;

	if (IS_ENABLED(CONFIG_HAVE_ARCH_JUMP_LABEL_RELATIVE))
		swapfn = jump_label_swap;

	size = (((unsigned long)stop - (unsigned long)start)
					/ sizeof(struct jump_entry));
	sort(start, size, sizeof(struct jump_entry), jump_label_cmp, swapfn);
}