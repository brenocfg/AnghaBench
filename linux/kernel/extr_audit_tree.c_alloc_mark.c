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
struct fsnotify_mark {int /*<<< orphan*/  mask; } ;
struct audit_tree_mark {struct fsnotify_mark mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_IN_IGNORED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_tree_group ; 
 int /*<<< orphan*/  audit_tree_mark_cachep ; 
 int /*<<< orphan*/  fsnotify_init_mark (struct fsnotify_mark*,int /*<<< orphan*/ ) ; 
 struct audit_tree_mark* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fsnotify_mark *alloc_mark(void)
{
	struct audit_tree_mark *amark;

	amark = kmem_cache_zalloc(audit_tree_mark_cachep, GFP_KERNEL);
	if (!amark)
		return NULL;
	fsnotify_init_mark(&amark->mark, audit_tree_group);
	amark->mark.mask = FS_IN_IGNORED;
	return &amark->mark;
}