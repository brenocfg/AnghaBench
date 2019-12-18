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
struct kprobe_blacklist_entry {unsigned long start_addr; unsigned long end_addr; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kallsyms_lookup_size_offset (unsigned long,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  kernel_text_address (unsigned long) ; 
 struct kprobe_blacklist_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprobe_blacklist ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int kprobe_add_ksym_blacklist(unsigned long entry)
{
	struct kprobe_blacklist_entry *ent;
	unsigned long offset = 0, size = 0;

	if (!kernel_text_address(entry) ||
	    !kallsyms_lookup_size_offset(entry, &size, &offset))
		return -EINVAL;

	ent = kmalloc(sizeof(*ent), GFP_KERNEL);
	if (!ent)
		return -ENOMEM;
	ent->start_addr = entry;
	ent->end_addr = entry + size;
	INIT_LIST_HEAD(&ent->list);
	list_add_tail(&ent->list, &kprobe_blacklist);

	return (int)size;
}