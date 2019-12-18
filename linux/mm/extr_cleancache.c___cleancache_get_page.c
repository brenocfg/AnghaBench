#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct cleancache_filekey {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__* i_sb; } ;
struct TYPE_9__ {int (* get_page ) (int,struct cleancache_filekey,int /*<<< orphan*/ ,struct page*) ;} ;
struct TYPE_8__ {int cleancache_poolid; } ;
struct TYPE_6__ {TYPE_5__* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  cleancache_failed_gets ; 
 scalar_t__ cleancache_get_key (TYPE_5__*,struct cleancache_filekey*) ; 
 TYPE_4__* cleancache_ops ; 
 int /*<<< orphan*/  cleancache_succ_gets ; 
 int stub1 (int,struct cleancache_filekey,int /*<<< orphan*/ ,struct page*) ; 

int __cleancache_get_page(struct page *page)
{
	int ret = -1;
	int pool_id;
	struct cleancache_filekey key = { .u.key = { 0 } };

	if (!cleancache_ops) {
		cleancache_failed_gets++;
		goto out;
	}

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	pool_id = page->mapping->host->i_sb->cleancache_poolid;
	if (pool_id < 0)
		goto out;

	if (cleancache_get_key(page->mapping->host, &key) < 0)
		goto out;

	ret = cleancache_ops->get_page(pool_id, key, page->index, page);
	if (ret == 0)
		cleancache_succ_gets++;
	else
		cleancache_failed_gets++;
out:
	return ret;
}