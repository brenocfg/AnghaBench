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
struct f2fs_nm_info {int /*<<< orphan*/  nat_root; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 unsigned int radix_tree_gang_lookup (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int __gang_lookup_nat_cache(struct f2fs_nm_info *nm_i,
		nid_t start, unsigned int nr, struct nat_entry **ep)
{
	return radix_tree_gang_lookup(&nm_i->nat_root, (void **)ep, start, nr);
}