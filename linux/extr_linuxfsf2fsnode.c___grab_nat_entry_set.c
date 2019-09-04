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
struct nat_entry_set {scalar_t__ entry_cnt; int /*<<< orphan*/  set; int /*<<< orphan*/  set_list; int /*<<< orphan*/  entry_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  nid; } ;
struct nat_entry {TYPE_1__ ni; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nat_set_root; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NAT_BLOCK_OFFSET (int /*<<< orphan*/ ) ; 
 struct nat_entry_set* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nat_entry_set*) ; 
 int /*<<< orphan*/  nat_entry_set_slab ; 
 struct nat_entry_set* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nat_entry_set *__grab_nat_entry_set(struct f2fs_nm_info *nm_i,
							struct nat_entry *ne)
{
	nid_t set = NAT_BLOCK_OFFSET(ne->ni.nid);
	struct nat_entry_set *head;

	head = radix_tree_lookup(&nm_i->nat_set_root, set);
	if (!head) {
		head = f2fs_kmem_cache_alloc(nat_entry_set_slab, GFP_NOFS);

		INIT_LIST_HEAD(&head->entry_list);
		INIT_LIST_HEAD(&head->set_list);
		head->set = set;
		head->entry_cnt = 0;
		f2fs_radix_tree_insert(&nm_i->nat_set_root, set, head);
	}
	return head;
}