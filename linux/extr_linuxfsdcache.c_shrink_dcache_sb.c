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
struct super_block {int /*<<< orphan*/  s_dentry_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dentry_lru_isolate_shrink ; 
 int /*<<< orphan*/  dispose ; 
 scalar_t__ list_lru_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shrink_dentry_list (int /*<<< orphan*/ *) ; 

void shrink_dcache_sb(struct super_block *sb)
{
	do {
		LIST_HEAD(dispose);

		list_lru_walk(&sb->s_dentry_lru,
			dentry_lru_isolate_shrink, &dispose, 1024);
		shrink_dentry_list(&dispose);
	} while (list_lru_count(&sb->s_dentry_lru) > 0);
}