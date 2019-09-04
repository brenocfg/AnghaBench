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
struct TYPE_18__ {int /*<<< orphan*/  flow; int /*<<< orphan*/  latest_nodes; int /*<<< orphan*/  idx; } ;
struct TYPE_17__ {int /*<<< orphan*/  content; } ;
struct TYPE_16__ {scalar_t__ user; } ;
struct TYPE_15__ {scalar_t__ data; } ;
typedef  TYPE_1__ RGraphNode ;
typedef  TYPE_2__ RAnalEsil ;
typedef  TYPE_3__ EsilDataFlowNode ;
typedef  TYPE_4__ EsilDataFlow ;
typedef  int /*<<< orphan*/  (* AddConstraintStringUseNewCB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 TYPE_3__* new_edf_node (TYPE_4__*,char const*) ; 
 int r_anal_esil_push (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* r_graph_add_node (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* sdb_ptr_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edf_use_new_push_1(RAnalEsil *esil, const char *op_string, AddConstraintStringUseNewCB cb) {
	EsilDataFlow *edf = (EsilDataFlow *)esil->user;
	RGraphNode *op_node = r_graph_add_node (edf->flow, new_edf_node (edf, op_string));
	RGraphNode *latest_new = sdb_ptr_get (edf->latest_nodes, "new", 0);	//node for esil->cur
	if (!latest_new) {
		return 0;
	}
	EsilDataFlowNode *result = new_edf_node (edf, "result_");
	r_strbuf_appendf(result->content, "%d", edf->idx++);
	if (cb) {
		EsilDataFlowNode *e_new_node = (EsilDataFlowNode *)latest_new->data;
		cb (result->content, r_strbuf_get (e_new_node->content));
	}
	RGraphNode *result_node = r_graph_add_node (edf->flow, result);
	sdb_ptr_set (edf->latest_nodes, r_strbuf_get(result->content), result_node, 0);
	r_graph_add_edge (edf->flow, latest_new, op_node);
	r_graph_add_edge (edf->flow, op_node, result_node);
	return r_anal_esil_push (esil, r_strbuf_get(result->content));
}