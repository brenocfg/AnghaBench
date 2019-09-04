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
struct send_ctx {int /*<<< orphan*/  name_cache; int /*<<< orphan*/  name_cache_size; TYPE_1__* send_root; } ;
struct name_cache_entry {scalar_t__ ino; int /*<<< orphan*/  list; int /*<<< orphan*/  radix_list; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,unsigned long) ; 
 struct list_head* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void name_cache_delete(struct send_ctx *sctx,
			      struct name_cache_entry *nce)
{
	struct list_head *nce_head;

	nce_head = radix_tree_lookup(&sctx->name_cache,
			(unsigned long)nce->ino);
	if (!nce_head) {
		btrfs_err(sctx->send_root->fs_info,
	      "name_cache_delete lookup failed ino %llu cache size %d, leaking memory",
			nce->ino, sctx->name_cache_size);
	}

	list_del(&nce->radix_list);
	list_del(&nce->list);
	sctx->name_cache_size--;

	/*
	 * We may not get to the final release of nce_head if the lookup fails
	 */
	if (nce_head && list_empty(nce_head)) {
		radix_tree_delete(&sctx->name_cache, (unsigned long)nce->ino);
		kfree(nce_head);
	}
}