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
struct assoc_array_delete_collapse_context {void const* skip_leaf; scalar_t__ slot; TYPE_1__* node; } ;
struct TYPE_2__ {int /*<<< orphan*/ * slots; } ;

/* Variables and functions */
 scalar_t__ ASSOC_ARRAY_FAN_OUT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assoc_array_leaf_to_ptr (void const*) ; 

__attribute__((used)) static int assoc_array_delete_collapse_iterator(const void *leaf,
						void *iterator_data)
{
	struct assoc_array_delete_collapse_context *collapse = iterator_data;

	if (leaf == collapse->skip_leaf)
		return 0;

	BUG_ON(collapse->slot >= ASSOC_ARRAY_FAN_OUT);

	collapse->node->slots[collapse->slot++] = assoc_array_leaf_to_ptr(leaf);
	return 0;
}