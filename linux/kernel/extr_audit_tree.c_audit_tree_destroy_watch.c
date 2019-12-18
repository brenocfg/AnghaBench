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
struct fsnotify_mark {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  audit_tree_mark_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_tree_destroy_watch(struct fsnotify_mark *mark)
{
	kmem_cache_free(audit_tree_mark_cachep, audit_mark(mark));
}