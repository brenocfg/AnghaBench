#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/  period; } ;
struct hist_entry {int /*<<< orphan*/  sorted_chain; TYPE_2__* stat_acc; TYPE_1__ stat; } ;
struct TYPE_8__ {int mode; } ;
struct TYPE_7__ {scalar_t__ cumulate_callchain; } ;
struct TYPE_6__ {int /*<<< orphan*/  period; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  CHAIN_FLAT 132 
#define  CHAIN_FOLDED 131 
#define  CHAIN_GRAPH_ABS 130 
#define  CHAIN_GRAPH_REL 129 
#define  CHAIN_NONE 128 
 size_t callchain__fprintf_flat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t callchain__fprintf_folded (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t callchain__fprintf_graph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ callchain_param ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_3__ symbol_conf ; 

__attribute__((used)) static size_t hist_entry_callchain__fprintf(struct hist_entry *he,
					    u64 total_samples, int left_margin,
					    FILE *fp)
{
	u64 parent_samples = he->stat.period;

	if (symbol_conf.cumulate_callchain)
		parent_samples = he->stat_acc->period;

	switch (callchain_param.mode) {
	case CHAIN_GRAPH_REL:
		return callchain__fprintf_graph(fp, &he->sorted_chain, total_samples,
						parent_samples, left_margin);
		break;
	case CHAIN_GRAPH_ABS:
		return callchain__fprintf_graph(fp, &he->sorted_chain, total_samples,
						parent_samples, left_margin);
		break;
	case CHAIN_FLAT:
		return callchain__fprintf_flat(fp, &he->sorted_chain, total_samples);
		break;
	case CHAIN_FOLDED:
		return callchain__fprintf_folded(fp, &he->sorted_chain, total_samples);
		break;
	case CHAIN_NONE:
		break;
	default:
		pr_err("Bad callchain mode\n");
	}

	return 0;
}