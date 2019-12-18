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
struct name_cache_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  radix_list; scalar_t__ ino; } ;
struct send_ctx {int /*<<< orphan*/  name_cache_size; struct name_cache_entry name_cache_list; int /*<<< orphan*/  name_cache; } ;
struct list_head {int /*<<< orphan*/  list; int /*<<< orphan*/  radix_list; scalar_t__ ino; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct name_cache_entry*) ; 
 int /*<<< orphan*/  kfree (struct name_cache_entry*) ; 
 struct name_cache_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct name_cache_entry*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,scalar_t__,struct name_cache_entry*) ; 
 struct name_cache_entry* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int name_cache_insert(struct send_ctx *sctx,
			     struct name_cache_entry *nce)
{
	int ret = 0;
	struct list_head *nce_head;

	nce_head = radix_tree_lookup(&sctx->name_cache,
			(unsigned long)nce->ino);
	if (!nce_head) {
		nce_head = kmalloc(sizeof(*nce_head), GFP_KERNEL);
		if (!nce_head) {
			kfree(nce);
			return -ENOMEM;
		}
		INIT_LIST_HEAD(nce_head);

		ret = radix_tree_insert(&sctx->name_cache, nce->ino, nce_head);
		if (ret < 0) {
			kfree(nce_head);
			kfree(nce);
			return ret;
		}
	}
	list_add_tail(&nce->radix_list, nce_head);
	list_add_tail(&nce->list, &sctx->name_cache_list);
	sctx->name_cache_size++;

	return ret;
}