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
typedef  int /*<<< orphan*/  work_func_t ;
struct page {int dummy; } ;
struct cifs_writedata {int /*<<< orphan*/  work; int /*<<< orphan*/  done; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; struct page** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cifs_writedata* kzalloc (int,int /*<<< orphan*/ ) ; 

struct cifs_writedata *
cifs_writedata_direct_alloc(struct page **pages, work_func_t complete)
{
	struct cifs_writedata *wdata;

	wdata = kzalloc(sizeof(*wdata), GFP_NOFS);
	if (wdata != NULL) {
		wdata->pages = pages;
		kref_init(&wdata->refcount);
		INIT_LIST_HEAD(&wdata->list);
		init_completion(&wdata->done);
		INIT_WORK(&wdata->work, complete);
	}
	return wdata;
}