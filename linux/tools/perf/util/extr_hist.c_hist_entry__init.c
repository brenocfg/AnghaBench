#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct res_sample {int dummy; } ;
struct TYPE_23__ {int /*<<< orphan*/  map; } ;
struct TYPE_17__ {int /*<<< orphan*/  node; } ;
struct TYPE_19__ {int /*<<< orphan*/  map; } ;
struct TYPE_18__ {int /*<<< orphan*/  map; } ;
struct TYPE_24__ {TYPE_3__ to; TYPE_2__ from; } ;
struct hist_entry {size_t callchain_size; int leaf; TYPE_8__* stat_acc; TYPE_7__ ms; TYPE_6__* mem_info; TYPE_8__* branch_info; TYPE_8__* raw_data; TYPE_8__* srcline; void* hroot_out; void* hroot_in; int /*<<< orphan*/  thread; TYPE_1__ pairs; int /*<<< orphan*/  res_samples; int /*<<< orphan*/  raw_size; int /*<<< orphan*/  callchain; TYPE_8__ stat; } ;
struct TYPE_25__ {int /*<<< orphan*/  report_hierarchy; scalar_t__ res_sample; scalar_t__ use_callchain; scalar_t__ cumulate_callchain; } ;
struct TYPE_21__ {int /*<<< orphan*/  map; } ;
struct TYPE_20__ {int /*<<< orphan*/  map; } ;
struct TYPE_22__ {TYPE_5__ daddr; TYPE_4__ iaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT_CACHED ; 
 int /*<<< orphan*/  callchain_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calloc (int,scalar_t__) ; 
 scalar_t__ hist_entry__has_callchains (struct hist_entry*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  map__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_8__*,int) ; 
 TYPE_8__* memdup (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* strdup (TYPE_8__*) ; 
 TYPE_9__ symbol_conf ; 
 int /*<<< orphan*/  thread__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_8__**) ; 

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
		if (he->branch_info == NULL)
			goto err;

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
		if (he->raw_data == NULL)
			goto err_infos;
	}

	if (he->srcline) {
		he->srcline = strdup(he->srcline);
		if (he->srcline == NULL)
			goto err_rawdata;
	}

	if (symbol_conf.res_sample) {
		he->res_samples = calloc(sizeof(struct res_sample),
					symbol_conf.res_sample);
		if (!he->res_samples)
			goto err_srcline;
	}

	INIT_LIST_HEAD(&he->pairs.node);
	thread__get(he->thread);
	he->hroot_in  = RB_ROOT_CACHED;
	he->hroot_out = RB_ROOT_CACHED;

	if (!symbol_conf.report_hierarchy)
		he->leaf = true;

	return 0;

err_srcline:
	zfree(&he->srcline);

err_rawdata:
	zfree(&he->raw_data);

err_infos:
	if (he->branch_info) {
		map__put(he->branch_info->from.map);
		map__put(he->branch_info->to.map);
		zfree(&he->branch_info);
	}
	if (he->mem_info) {
		map__put(he->mem_info->iaddr.map);
		map__put(he->mem_info->daddr.map);
	}
err:
	map__zput(he->ms.map);
	zfree(&he->stat_acc);
	return -ENOMEM;
}