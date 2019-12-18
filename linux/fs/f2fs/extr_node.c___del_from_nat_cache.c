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
struct nat_entry {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nat_cnt; int /*<<< orphan*/  nat_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_nat_entry (struct nat_entry*) ; 
 int /*<<< orphan*/  nat_get_nid (struct nat_entry*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __del_from_nat_cache(struct f2fs_nm_info *nm_i, struct nat_entry *e)
{
	radix_tree_delete(&nm_i->nat_root, nat_get_nid(e));
	nm_i->nat_cnt--;
	__free_nat_entry(e);
}