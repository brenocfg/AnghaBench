#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ user; } ;
struct TYPE_17__ {int /*<<< orphan*/  flow; int /*<<< orphan*/  idx; TYPE_1__* cur; } ;
struct TYPE_16__ {int /*<<< orphan*/  content; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {scalar_t__ data; } ;
typedef  TYPE_1__ RGraphNode ;
typedef  TYPE_2__ RAnalEsilDFGNode ;
typedef  TYPE_3__ RAnalEsilDFG ;
typedef  TYPE_4__ RAnalEsil ;
typedef  int /*<<< orphan*/  (* AddConstraintStringUseNewCB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_ESIL_DFG_BLOCK_RESULT ; 
 int /*<<< orphan*/  _edf_var_set (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* r_anal_esil_dfg_node_new (TYPE_3__*,char const*) ; 
 int r_anal_esil_push (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* r_graph_add_node (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool edf_use_new_push_1(RAnalEsil *esil, const char *op_string, AddConstraintStringUseNewCB cb) {
	RAnalEsilDFG *edf = (RAnalEsilDFG *)esil->user;
	RGraphNode *op_node = r_graph_add_node (edf->flow, r_anal_esil_dfg_node_new (edf, op_string));
	RGraphNode *latest_new = edf->cur;
	if (!latest_new) {
		return 0;
	}
	RAnalEsilDFGNode *result = r_anal_esil_dfg_node_new (edf, "result_");
	result->type = R_ANAL_ESIL_DFG_BLOCK_RESULT; // is this generative?
	r_strbuf_appendf (result->content, "%d", edf->idx++);
	if (cb) {
		RAnalEsilDFGNode *e_new_node = (RAnalEsilDFGNode *)latest_new->data;
		cb (result->content, r_strbuf_get (e_new_node->content));
	}
	RGraphNode *result_node = r_graph_add_node (edf->flow, result);
	_edf_var_set (edf, r_strbuf_get (result->content), result_node);
	r_graph_add_edge (edf->flow, latest_new, op_node);
	r_graph_add_edge (edf->flow, op_node, result_node);
	return r_anal_esil_push (esil, r_strbuf_get (result->content));
}