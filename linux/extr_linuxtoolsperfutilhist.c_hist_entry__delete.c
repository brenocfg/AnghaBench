#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct hist_entry_ops {int /*<<< orphan*/  (* free ) (struct hist_entry*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
struct hist_entry {scalar_t__* raw_data; scalar_t__* trace_output; int /*<<< orphan*/  callchain; scalar_t__* srcfile; int /*<<< orphan*/  srcline; TYPE_6__* stat_acc; TYPE_7__* mem_info; TYPE_6__* branch_info; TYPE_1__ ms; int /*<<< orphan*/  thread; struct hist_entry_ops* ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  map; } ;
struct TYPE_11__ {int /*<<< orphan*/  map; } ;
struct TYPE_14__ {TYPE_5__ daddr; TYPE_4__ iaddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_13__ {int /*<<< orphan*/  srcline_to; int /*<<< orphan*/  srcline_from; TYPE_3__ to; TYPE_2__ from; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  free_callchain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_srcline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_info__zput (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (struct hist_entry*) ; 
 int /*<<< orphan*/  thread__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_6__**) ; 

void hist_entry__delete(struct hist_entry *he)
{
	struct hist_entry_ops *ops = he->ops;

	thread__zput(he->thread);
	map__zput(he->ms.map);

	if (he->branch_info) {
		map__zput(he->branch_info->from.map);
		map__zput(he->branch_info->to.map);
		free_srcline(he->branch_info->srcline_from);
		free_srcline(he->branch_info->srcline_to);
		zfree(&he->branch_info);
	}

	if (he->mem_info) {
		map__zput(he->mem_info->iaddr.map);
		map__zput(he->mem_info->daddr.map);
		mem_info__zput(he->mem_info);
	}

	zfree(&he->stat_acc);
	free_srcline(he->srcline);
	if (he->srcfile && he->srcfile[0])
		free(he->srcfile);
	free_callchain(he->callchain);
	free(he->trace_output);
	free(he->raw_data);
	ops->free(he);
}