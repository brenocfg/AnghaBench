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
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_F2FS_ZERO ; 
 struct nat_entry* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nat_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat_entry_slab ; 
 int /*<<< orphan*/  nat_reset_flag (struct nat_entry*) ; 
 int /*<<< orphan*/  nat_set_nid (struct nat_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nat_entry *__alloc_nat_entry(nid_t nid, bool no_fail)
{
	struct nat_entry *new;

	if (no_fail)
		new = f2fs_kmem_cache_alloc(nat_entry_slab, GFP_F2FS_ZERO);
	else
		new = kmem_cache_alloc(nat_entry_slab, GFP_F2FS_ZERO);
	if (new) {
		nat_set_nid(new, nid);
		nat_reset_flag(new);
	}
	return new;
}