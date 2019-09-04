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
struct nat_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  ni; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nat_cnt; int /*<<< orphan*/  nat_list_lock; int /*<<< orphan*/  nat_entries; int /*<<< orphan*/  nat_root; } ;
struct f2fs_nat_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  f2fs_radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nat_entry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat_get_nid (struct nat_entry*) ; 
 int /*<<< orphan*/  node_info_from_raw_nat (int /*<<< orphan*/ *,struct f2fs_nat_entry*) ; 
 scalar_t__ radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nat_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nat_entry *__init_nat_entry(struct f2fs_nm_info *nm_i,
	struct nat_entry *ne, struct f2fs_nat_entry *raw_ne, bool no_fail)
{
	if (no_fail)
		f2fs_radix_tree_insert(&nm_i->nat_root, nat_get_nid(ne), ne);
	else if (radix_tree_insert(&nm_i->nat_root, nat_get_nid(ne), ne))
		return NULL;

	if (raw_ne)
		node_info_from_raw_nat(&ne->ni, raw_ne);

	spin_lock(&nm_i->nat_list_lock);
	list_add_tail(&ne->list, &nm_i->nat_entries);
	spin_unlock(&nm_i->nat_list_lock);

	nm_i->nat_cnt++;
	return ne;
}