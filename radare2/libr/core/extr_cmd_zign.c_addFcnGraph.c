#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bbs; } ;
struct TYPE_11__ {int /*<<< orphan*/  anal; } ;
struct TYPE_10__ {int /*<<< orphan*/  bbsum; int /*<<< orphan*/  ebbs; int /*<<< orphan*/  edges; int /*<<< orphan*/  nbbs; int /*<<< orphan*/  cc; } ;
typedef  TYPE_1__ RSignGraph ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_fcn_cc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  r_anal_fcn_count_edges (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_fcn_size (TYPE_3__*) ; 
 int /*<<< orphan*/  r_list_length (int /*<<< orphan*/ ) ; 
 int r_sign_add_graph (int /*<<< orphan*/ ,char const*,TYPE_1__) ; 

__attribute__((used)) static bool addFcnGraph(RCore *core, RAnalFunction *fcn, const char *name) {
	RSignGraph graph = {
		.cc = r_anal_fcn_cc (core->anal, fcn),
		.nbbs = r_list_length (fcn->bbs)
	};
	// XXX ebbs doesnt gets initialized if calling this from inside the struct
	graph.edges = r_anal_fcn_count_edges (fcn, &graph.ebbs);
	graph.bbsum = r_anal_fcn_size (fcn);
	return r_sign_add_graph (core->anal, name, graph);
}