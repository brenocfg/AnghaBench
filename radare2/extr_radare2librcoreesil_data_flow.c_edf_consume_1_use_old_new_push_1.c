#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  flow; int /*<<< orphan*/  latest_nodes; int /*<<< orphan*/  idx; } ;
struct TYPE_19__ {int /*<<< orphan*/  content; } ;
struct TYPE_18__ {scalar_t__ user; } ;
struct TYPE_17__ {scalar_t__ data; } ;
typedef  TYPE_1__ RGraphNode ;
typedef  TYPE_2__ RAnalEsil ;
typedef  TYPE_3__ EsilDataFlowNode ;
typedef  TYPE_4__ EsilDataFlow ;
typedef  int /*<<< orphan*/  (* AddConstraintStringConsume1UseOldNewCB ) (int /*<<< orphan*/ ,char*,char*,char*) ;

/* Variables and functions */
 int R_ANAL_ESIL_PARM_NUM ; 
 int R_ANAL_ESIL_PARM_REG ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_3__* new_edf_node (TYPE_4__*,char*) ; 
 int r_anal_esil_get_parm_type (TYPE_2__*,char*) ; 
 char* r_anal_esil_pop (TYPE_2__*) ; 
 int r_anal_esil_push (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* r_graph_add_node (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* r_strbuf_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* sdb_ptr_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edf_consume_1_use_old_new_push_1 (RAnalEsil *esil, const char *op_string, AddConstraintStringConsume1UseOldNewCB cb) {
	EsilDataFlow *edf = (EsilDataFlow *)esil->user;
	char *src = r_anal_esil_pop (esil);

	if (!src) {
		free (src);
		return 0;
	}
	EsilDataFlowNode *eop_node = new_edf_node (edf, src);
	r_strbuf_appendf (eop_node->content, ",%s", op_string);
	RGraphNode *src_node, *op_node = r_graph_add_node (edf->flow, eop_node);
	src_node = sdb_ptr_get (edf->latest_nodes, src, 0);
	if (!src_node) {
		int src_type = r_anal_esil_get_parm_type (esil, src);
#if 0
		//TODO: better input validation
		if (src_type == R_ANAL_ESIL_PARM_INVALID) {
			free (dst);
			free (src);
			return 0;
		}
#endif
		if (src_type == R_ANAL_ESIL_PARM_NUM) {
			RGraphNode *n_value = r_graph_add_node (edf->flow, new_edf_node (edf, src));
			EsilDataFlowNode *ec_node = new_edf_node (edf, src);
			r_strbuf_appendf (ec_node->content, ":const_%d", edf->idx++);
			src_node = r_graph_add_node (edf->flow, ec_node);
			r_graph_add_edge (edf->flow, n_value, src_node);
		}
		if (src_type == R_ANAL_ESIL_PARM_REG) {
			RGraphNode *n_reg = r_graph_add_node (edf->flow, new_edf_node (edf, src));
			EsilDataFlowNode *ev_node = new_edf_node (edf, src);
			r_strbuf_appendf(ev_node->content, ":var_%d", edf->idx++);
			src_node = r_graph_add_node (edf->flow, ev_node);
			sdb_ptr_set (edf->latest_nodes, src, src_node, 0);
			r_graph_add_edge (edf->flow, n_reg, src_node);
		}
		// ignore internal vars for now
	}

	free (src);

	r_graph_add_edge (edf->flow, src_node, op_node);

	RGraphNode *latest_new = sdb_ptr_get(edf->latest_nodes, "new", 0);
	RGraphNode *latest_old = sdb_ptr_get(edf->latest_nodes, "old", 0);
	EsilDataFlowNode *result = new_edf_node (edf, "result_");
	r_strbuf_appendf(result->content, "%d", edf->idx++);
	if (cb) {
		EsilDataFlowNode *e_src_node = (EsilDataFlowNode *)src_node->data;
		EsilDataFlowNode *e_new_node = (EsilDataFlowNode *)latest_new->data;
		EsilDataFlowNode *e_old_node = (EsilDataFlowNode *)latest_old->data;
		cb (result->content, r_strbuf_get (e_src_node->content),
				r_strbuf_get (e_new_node->content), r_strbuf_get (e_old_node->content));
	}
	RGraphNode *result_node = r_graph_add_node (edf->flow, result);
	sdb_ptr_set (edf->latest_nodes, r_strbuf_get(result->content), result_node, 0);
	r_graph_add_edge (edf->flow, latest_new, op_node);
	r_graph_add_edge (edf->flow, latest_old, op_node);
	r_graph_add_edge (edf->flow, op_node, result_node);
	return r_anal_esil_push (esil, r_strbuf_get(result->content));
}