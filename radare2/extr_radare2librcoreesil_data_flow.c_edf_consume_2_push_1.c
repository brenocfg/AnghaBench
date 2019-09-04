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
typedef  int ut32 ;
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
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* r_strbuf_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdb_ptr_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edf_consume_2_push_1 (RAnalEsil *esil, const char *op_string) {
	EsilDataFlow *edf = (EsilDataFlow *)esil->user;
	char *src[2] = {r_anal_esil_pop (esil), r_anal_esil_pop (esil)};

	if (!src[0] || !src[1]) {
		free (src[0]);
		free (src[1]);
		return 0;
	}
	EsilDataFlowNode *eop_node = new_edf_node (edf, src[0]);
	r_strbuf_appendf (eop_node->content, ",%s,%s", src[1], op_string);
	RGraphNode *op_node = r_graph_add_node (edf->flow, eop_node);
	RGraphNode *src_node[2];
	ut32 i; 
	for (i = 0; i < 2; i++) {
		src_node[i] = sdb_ptr_get (edf->latest_nodes, src[i], 0);
		if (!src_node[i]) {
			int src_type = r_anal_esil_get_parm_type (esil, src[i]);
#if 0
			//TODO: better input validation
			if (src_type == R_ANAL_ESIL_PARM_INVALID) {
				free (dst);
				free (src);
				return 0;
			}
#endif

			if (src_type == R_ANAL_ESIL_PARM_NUM) {
				RGraphNode *n_value = r_graph_add_node (edf->flow, new_edf_node (edf, src[i]));
				EsilDataFlowNode *ec_node = new_edf_node (edf, src[i]);
				r_strbuf_appendf(ec_node->content, ":const_%d", edf->idx++);
				src_node[i] = r_graph_add_node (edf->flow, ec_node);
				r_graph_add_edge (edf->flow, n_value, src_node[i]);
			}
			if (src_type == R_ANAL_ESIL_PARM_REG) {
				RGraphNode *n_reg = r_graph_add_node (edf->flow, new_edf_node (edf, src[i]));
				EsilDataFlowNode *ev_node = new_edf_node (edf, src[i]);
				r_strbuf_appendf(ev_node->content, ":var_%d", edf->idx++);
				src_node[i] = r_graph_add_node (edf->flow, ev_node);
				sdb_ptr_set (edf->latest_nodes, src[i], src_node[i], 0);
				r_graph_add_edge (edf->flow, n_reg, src_node[i]);
			}
			// ignore internal vars for now
		}
		r_graph_add_edge (edf->flow, src_node[i], op_node);
	}

	free (src[0]);
	free (src[1]);

	EsilDataFlowNode *result = new_edf_node (edf, "result_");
	r_strbuf_appendf (result->content, "%d", edf->idx++);
	RGraphNode *result_node = r_graph_add_node (edf->flow, result);
	r_graph_add_edge (edf->flow, op_node, result_node);
	sdb_ptr_set (edf->latest_nodes, r_strbuf_get (result->content), result_node, 0);
	r_anal_esil_push (esil, r_strbuf_get (result->content));
	return 1;
}