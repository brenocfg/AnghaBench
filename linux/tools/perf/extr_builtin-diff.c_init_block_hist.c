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
struct TYPE_2__ {int /*<<< orphan*/  sort; int /*<<< orphan*/  cmp; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  list; } ;
struct block_hist {int valid; TYPE_1__ block_fmt; int /*<<< orphan*/  block_list; int /*<<< orphan*/  block_hists; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __hists__init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_cmp ; 
 int /*<<< orphan*/  block_sort ; 
 int /*<<< orphan*/  perf_hpp_list__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_hpp_list__register_sort_field (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void init_block_hist(struct block_hist *bh)
{
	__hists__init(&bh->block_hists, &bh->block_list);
	perf_hpp_list__init(&bh->block_list);

	INIT_LIST_HEAD(&bh->block_fmt.list);
	INIT_LIST_HEAD(&bh->block_fmt.sort_list);
	bh->block_fmt.cmp = block_cmp;
	bh->block_fmt.sort = block_sort;
	perf_hpp_list__register_sort_field(&bh->block_list,
					   &bh->block_fmt);
	bh->valid = true;
}