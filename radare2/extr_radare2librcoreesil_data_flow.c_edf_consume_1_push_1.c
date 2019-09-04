#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  latest_nodes; int /*<<< orphan*/  flow; int /*<<< orphan*/  idx; } ;
struct TYPE_12__ {int /*<<< orphan*/  content; } ;
struct TYPE_11__ {scalar_t__ user; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_1__ RAnalEsil ;
typedef  TYPE_2__ EsilDataFlowNode ;
typedef  TYPE_3__ EsilDataFlow ;

/* Variables and functions */
 int R_ANAL_ESIL_PARM_NUM ; 
 int R_ANAL_ESIL_PARM_REG ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* new_edf_node (TYPE_3__*,char*) ; 
 int r_anal_esil_get_parm_type (TYPE_1__*,char*) ; 
 char* r_anal_esil_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  r_anal_esil_push (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_graph_add_node (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* r_strbuf_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdb_ptr_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edf_consume_1_push_1(RAnalEsil *esil, const char *op_string) {
	EsilDataFlow *edf = (EsilDataFlow *)esil->user;
	char *src = r_anal_esil_pop (esil);
	if (!src) {
		return 0;
	}
	EsilDataFlowNode *eop_node = new_edf_node (edf, src);
	r_strbuf_appendf (eop_node->content, ",%s", op_string);
	RGraphNode *op_node = r_graph_add_node (edf->flow, eop_node);
	RGraphNode *src_node = sdb_ptr_get (edf->latest_nodes, src, 0);
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

	EsilDataFlowNode *result = new_edf_node (edf, "result_");
	r_strbuf_appendf (result->content, "%d", edf->idx++);
	RGraphNode *result_node = r_graph_add_node (edf->flow, result);
	r_graph_add_edge (edf->flow, op_node, result_node);
	sdb_ptr_set (edf->latest_nodes, r_strbuf_get (result->content), result_node, 0);
	r_anal_esil_push (esil, r_strbuf_get (result->content));
	return 1;
}