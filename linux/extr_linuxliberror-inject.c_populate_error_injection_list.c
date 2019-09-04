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
struct error_injection_entry {int /*<<< orphan*/  etype; scalar_t__ addr; } ;
struct ei_entry {unsigned long start_addr; unsigned long end_addr; int /*<<< orphan*/  list; void* priv; int /*<<< orphan*/  etype; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long arch_deref_entry_point (void*) ; 
 int /*<<< orphan*/  ei_mutex ; 
 int /*<<< orphan*/  error_injection_list ; 
 int /*<<< orphan*/  kallsyms_lookup_size_offset (unsigned long,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  kernel_text_address (unsigned long) ; 
 struct ei_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,void*) ; 

__attribute__((used)) static void populate_error_injection_list(struct error_injection_entry *start,
					  struct error_injection_entry *end,
					  void *priv)
{
	struct error_injection_entry *iter;
	struct ei_entry *ent;
	unsigned long entry, offset = 0, size = 0;

	mutex_lock(&ei_mutex);
	for (iter = start; iter < end; iter++) {
		entry = arch_deref_entry_point((void *)iter->addr);

		if (!kernel_text_address(entry) ||
		    !kallsyms_lookup_size_offset(entry, &size, &offset)) {
			pr_err("Failed to find error inject entry at %p\n",
				(void *)entry);
			continue;
		}

		ent = kmalloc(sizeof(*ent), GFP_KERNEL);
		if (!ent)
			break;
		ent->start_addr = entry;
		ent->end_addr = entry + size;
		ent->etype = iter->etype;
		ent->priv = priv;
		INIT_LIST_HEAD(&ent->list);
		list_add_tail(&ent->list, &error_injection_list);
	}
	mutex_unlock(&ei_mutex);
}