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
struct TYPE_12__ {int /*<<< orphan*/  latest_nodes; int /*<<< orphan*/  flow; int /*<<< orphan*/  idx; } ;
struct TYPE_11__ {int /*<<< orphan*/  content; } ;
struct TYPE_10__ {scalar_t__ user; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_1__ RAnalEsil ;
typedef  TYPE_2__ EsilDataFlowNode ;
typedef  TYPE_3__ EsilDataFlow ;

/* Variables and functions */
 int R_ANAL_ESIL_PARM_INVALID ; 
 int R_ANAL_ESIL_PARM_NUM ; 
 int R_ANAL_ESIL_PARM_REG ; 
 int /*<<< orphan*/  eprintf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* new_edf_node (TYPE_3__*,char*) ; 
 int r_anal_esil_get_parm_type (TYPE_1__*,char*) ; 
 char* r_anal_esil_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_graph_add_node (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/ * sdb_ptr_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edf_consume_2_set_reg (RAnalEsil *esil, const char *op_string) {
	if (!esil) {
		return 0;
	}
	EsilDataFlow *edf = (EsilDataFlow *)esil->user;
	char *dst = r_anal_esil_pop (esil);
	char *src = r_anal_esil_pop (esil);

	int dst_type = r_anal_esil_get_parm_type (esil, dst);
	if (dst_type == R_ANAL_ESIL_PARM_INVALID) {
		free (dst);
		free (src);
		return 0;
	}
	
	if (!src) {
		free (dst);
		return 0;
	}
	// could be an abstract value
	RGraphNode *src_node = sdb_ptr_get (edf->latest_nodes, src, 0);
	if (!src_node) {
		int src_type = r_anal_esil_get_parm_type (esil, src);
		if (src_type == R_ANAL_ESIL_PARM_INVALID) {
			free (dst);
			free (src);
			return 0;
		}
	
		if (src_type == R_ANAL_ESIL_PARM_NUM) {
			RGraphNode *n_value = r_graph_add_node (edf->flow, new_edf_node (edf, src));
			EsilDataFlowNode *ec_node = new_edf_node (edf, src);
			r_strbuf_appendf(ec_node->content, ":const_%d", edf->idx++);
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
	} else {
		eprintf ("abstract: %s:%p\n", src, src_node);
	}

	RGraphNode *dst_node = sdb_ptr_get (edf->latest_nodes, dst, 0);
	if (!dst_node) {
		if (dst_type == R_ANAL_ESIL_PARM_REG) {
			RGraphNode *n_reg = r_graph_add_node (edf->flow, new_edf_node (edf, dst));
			EsilDataFlowNode *ev_node = new_edf_node (edf, dst);
			r_strbuf_appendf(ev_node->content, ":var_%d", edf->idx++);
			dst_node = r_graph_add_node (edf->flow, ev_node);
//			sdb_ptr_set (edf->latest_nodes, dst, ev_node, 0);
			r_graph_add_edge (edf->flow, n_reg, dst_node);
		}
	}

	if (!src_node || !dst_node) {
		free (src);
		free (dst);
		return 0;
	}

	EsilDataFlowNode *eop_node = new_edf_node (edf, src);
	r_strbuf_appendf (eop_node->content, ",%s,%s", dst, op_string);
	free (src);

	RGraphNode *op_node = r_graph_add_node (edf->flow, eop_node);
	r_graph_add_edge (edf->flow, dst_node, op_node);
	r_graph_add_edge (edf->flow, src_node, op_node);
	sdb_ptr_set (edf->latest_nodes, "old", dst_node, 0);		//esil->old
	EsilDataFlowNode *result = new_edf_node (edf, dst);
	r_strbuf_appendf(result->content, ":var_%d", edf->idx++);
	dst_node = r_graph_add_node (edf->flow, result);
	r_graph_add_edge (edf->flow, op_node, dst_node);
	sdb_ptr_set (edf->latest_nodes, dst, dst_node, 0);
	sdb_ptr_set (edf->latest_nodes, "new", dst_node, 0);		//esil->new
	free (dst);
	return 1;
}