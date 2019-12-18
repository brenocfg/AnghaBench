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
struct nat_entry {int /*<<< orphan*/  list; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nat_list_lock; int /*<<< orphan*/  nat_entries; int /*<<< orphan*/  nat_root; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DIRTY ; 
 int /*<<< orphan*/  get_nat_flag (struct nat_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nat_entry* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nat_entry *__lookup_nat_cache(struct f2fs_nm_info *nm_i, nid_t n)
{
	struct nat_entry *ne;

	ne = radix_tree_lookup(&nm_i->nat_root, n);

	/* for recent accessed nat entry, move it to tail of lru list */
	if (ne && !get_nat_flag(ne, IS_DIRTY)) {
		spin_lock(&nm_i->nat_list_lock);
		if (!list_empty(&ne->list))
			list_move_tail(&ne->list, &nm_i->nat_entries);
		spin_unlock(&nm_i->nat_list_lock);
	}

	return ne;
}