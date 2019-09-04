#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  node; } ;
struct TYPE_13__ {int /*<<< orphan*/  map; } ;
struct TYPE_15__ {int /*<<< orphan*/  map; } ;
struct TYPE_14__ {int /*<<< orphan*/  map; } ;
struct TYPE_21__ {TYPE_3__ to; TYPE_2__ from; } ;
struct hist_entry {size_t callchain_size; int leaf; void* hroot_out; void* hroot_in; int /*<<< orphan*/  thread; TYPE_7__ pairs; TYPE_9__* stat_acc; TYPE_6__* mem_info; TYPE_9__* branch_info; TYPE_1__ ms; int /*<<< orphan*/ * raw_data; int /*<<< orphan*/  raw_size; int /*<<< orphan*/  callchain; TYPE_9__ stat; } ;
struct TYPE_20__ {int /*<<< orphan*/  report_hierarchy; scalar_t__ use_callchain; scalar_t__ cumulate_callchain; } ;
struct TYPE_17__ {int /*<<< orphan*/  map; } ;
struct TYPE_16__ {int /*<<< orphan*/  map; } ;
struct TYPE_18__ {TYPE_5__ daddr; TYPE_4__ iaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  callchain_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_9__*) ; 
 scalar_t__ hist_entry__has_callchains (struct hist_entry*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  map__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/ * memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 TYPE_8__ symbol_conf ; 
 int /*<<< orphan*/  thread__get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_entry__init(struct hist_entry *he,
			    struct hist_entry *template,
			    bool sample_self,
			    size_t callchain_size)
{
	*he = *template;
	he->callchain_size = callchain_size;

	if (symbol_conf.cumulate_callchain) {
		he->stat_acc = malloc(sizeof(he->stat));
		if (he->stat_acc == NULL)
			return -ENOMEM;
		memcpy(he->stat_acc, &he->stat, sizeof(he->stat));
		if (!sample_self)
			memset(&he->stat, 0, sizeof(he->stat));
	}

	map__get(he->ms.map);

	if (he->branch_info) {
		/*
		 * This branch info is (a part of) allocated from
		 * sample__resolve_bstack() and will be freed after
		 * adding new entries.  So we need to save a copy.
		 */
		he->branch_info = malloc(sizeof(*he->branch_info));
		if (he->branch_info == NULL) {
			map__zput(he->ms.map);
			free(he->stat_acc);
			return -ENOMEM;
		}

		memcpy(he->branch_info, template->branch_info,
		       sizeof(*he->branch_info));

		map__get(he->branch_info->from.map);
		map__get(he->branch_info->to.map);
	}

	if (he->mem_info) {
		map__get(he->mem_info->iaddr.map);
		map__get(he->mem_info->daddr.map);
	}

	if (hist_entry__has_callchains(he) && symbol_conf.use_callchain)
		callchain_init(he->callchain);

	if (he->raw_data) {
		he->raw_data = memdup(he->raw_data, he->raw_size);

		if (he->raw_data == NULL) {
			map__put(he->ms.map);
			if (he->branch_info) {
				map__put(he->branch_info->from.map);
				map__put(he->branch_info->to.map);
				free(he->branch_info);
			}
			if (he->mem_info) {
				map__put(he->mem_info->iaddr.map);
				map__put(he->mem_info->daddr.map);
			}
			free(he->stat_acc);
			return -ENOMEM;
		}
	}
	INIT_LIST_HEAD(&he->pairs.node);
	thread__get(he->thread);
	he->hroot_in  = RB_ROOT;
	he->hroot_out = RB_ROOT;

	if (!symbol_conf.report_hierarchy)
		he->leaf = true;

	return 0;
}