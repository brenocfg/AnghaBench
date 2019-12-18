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
struct xa_node {void** slots; unsigned long shift; } ;

/* Variables and functions */
 unsigned long XA_CHUNK_SIZE ; 
 int /*<<< orphan*/  pr_cont (char*,void const*,...) ; 
 int /*<<< orphan*/  xa_dump_index (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  xa_dump_node (struct xa_node*) ; 
 int /*<<< orphan*/  xa_is_internal (void const*) ; 
 scalar_t__ xa_is_node (void const*) ; 
 scalar_t__ xa_is_retry (void const*) ; 
 scalar_t__ xa_is_sibling (void const*) ; 
 scalar_t__ xa_is_value (void const*) ; 
 scalar_t__ xa_is_zero (void const*) ; 
 void const* xa_to_internal (void const*) ; 
 struct xa_node* xa_to_node (void const*) ; 
 void const* xa_to_sibling (void const*) ; 
 int /*<<< orphan*/  xa_to_value (void const*) ; 

void xa_dump_entry(const void *entry, unsigned long index, unsigned long shift)
{
	if (!entry)
		return;

	xa_dump_index(index, shift);

	if (xa_is_node(entry)) {
		if (shift == 0) {
			pr_cont("%px\n", entry);
		} else {
			unsigned long i;
			struct xa_node *node = xa_to_node(entry);
			xa_dump_node(node);
			for (i = 0; i < XA_CHUNK_SIZE; i++)
				xa_dump_entry(node->slots[i],
				      index + (i << node->shift), node->shift);
		}
	} else if (xa_is_value(entry))
		pr_cont("value %ld (0x%lx) [%px]\n", xa_to_value(entry),
						xa_to_value(entry), entry);
	else if (!xa_is_internal(entry))
		pr_cont("%px\n", entry);
	else if (xa_is_retry(entry))
		pr_cont("retry (%ld)\n", xa_to_internal(entry));
	else if (xa_is_sibling(entry))
		pr_cont("sibling (slot %ld)\n", xa_to_sibling(entry));
	else if (xa_is_zero(entry))
		pr_cont("zero (%ld)\n", xa_to_internal(entry));
	else
		pr_cont("UNKNOWN ENTRY (%px)\n", entry);
}