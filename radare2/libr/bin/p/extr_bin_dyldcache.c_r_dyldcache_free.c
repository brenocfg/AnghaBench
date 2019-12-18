#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* accel; struct TYPE_4__* maps; struct TYPE_4__* hdr; int /*<<< orphan*/ * rebase_info; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * bins; } ;
typedef  TYPE_1__ RDyldCache ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebase_info_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_dyldcache_free(RDyldCache *cache) {
	if (!cache) {
		return;
	}

	r_list_free (cache->bins);
	cache->bins = NULL;
	r_buf_free (cache->buf);
	cache->buf = NULL;
	rebase_info_free (cache->rebase_info);
	cache->rebase_info = NULL;
	R_FREE (cache->hdr);
	R_FREE (cache->maps);
	R_FREE (cache->accel);
	R_FREE (cache);
}