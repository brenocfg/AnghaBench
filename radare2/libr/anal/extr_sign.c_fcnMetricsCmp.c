#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  bbs; } ;
struct TYPE_10__ {int cc; int nbbs; int edges; int ebbs; scalar_t__ bbsum; } ;
struct TYPE_9__ {TYPE_2__* graph; } ;
typedef  TYPE_1__ RSignItem ;
typedef  TYPE_2__ RSignGraph ;
typedef  TYPE_3__ RAnalFunction ;

/* Variables and functions */
 scalar_t__ matchCount (scalar_t__,int /*<<< orphan*/ ) ; 
 int r_anal_fcn_cc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int r_anal_fcn_count_edges (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  r_anal_fcn_size (TYPE_3__*) ; 
 int r_list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fcnMetricsCmp(RSignItem *it, RAnalFunction *fcn) {
	RSignGraph *graph = it->graph;
	int ebbs = -1;

	if (graph->cc != -1 && graph->cc != r_anal_fcn_cc (NULL, fcn)) {
		return false;
	}
	if (graph->nbbs != -1 && graph->nbbs != r_list_length (fcn->bbs)) {
		return false;
	}
	if (graph->edges != -1 && graph->edges != r_anal_fcn_count_edges (fcn, &ebbs)) {
		return false;
	}
	if (graph->ebbs != -1 && graph->ebbs != ebbs) {
		return false;
	}
	if (graph->bbsum > 0 && matchCount (graph->bbsum, r_anal_fcn_size (fcn))) {
		return false;
	}
	return true;
}