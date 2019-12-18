#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {TYPE_2__* object; } ;
struct fscache_retrieval {int /*<<< orphan*/  mapping; TYPE_3__ op; } ;
struct fscache_cookie {int /*<<< orphan*/  netfs_data; TYPE_1__* def; } ;
struct TYPE_5__ {struct fscache_cookie* cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mark_page_cached ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ TestSetPageFsCache (struct page*) ; 
 int /*<<< orphan*/  _debug (char*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_n_marks ; 
 int /*<<< orphan*/  fscache_page_cached ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  trace_fscache_page (struct fscache_cookie*,struct page*,int /*<<< orphan*/ ) ; 

void fscache_mark_page_cached(struct fscache_retrieval *op, struct page *page)
{
	struct fscache_cookie *cookie = op->op.object->cookie;

#ifdef CONFIG_FSCACHE_STATS
	atomic_inc(&fscache_n_marks);
#endif

	trace_fscache_page(cookie, page, fscache_page_cached);

	_debug("- mark %p{%lx}", page, page->index);
	if (TestSetPageFsCache(page)) {
		static bool once_only;
		if (!once_only) {
			once_only = true;
			pr_warn("Cookie type %s marked page %lx multiple times\n",
				cookie->def->name, page->index);
		}
	}

	if (cookie->def->mark_page_cached)
		cookie->def->mark_page_cached(cookie->netfs_data,
					      op->mapping, page);
}