#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* current_opstr; scalar_t__ user; } ;
struct TYPE_15__ {int /*<<< orphan*/ * cur; int /*<<< orphan*/  flow; int /*<<< orphan*/  idx; int /*<<< orphan*/ * old; } ;
struct TYPE_14__ {int type; int /*<<< orphan*/  content; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_1__ RAnalEsilDFGNode ;
typedef  TYPE_2__ RAnalEsilDFG ;
typedef  TYPE_3__ RAnalEsil ;

/* Variables and functions */
 int R_ANAL_ESIL_DFG_BLOCK_CONST ; 
 int R_ANAL_ESIL_DFG_BLOCK_GENERATIVE ; 
 int R_ANAL_ESIL_DFG_BLOCK_RESULT ; 
 int R_ANAL_ESIL_DFG_BLOCK_VAR ; 
 int R_ANAL_ESIL_PARM_INVALID ; 
 int const R_ANAL_ESIL_PARM_NUM ; 
 int const R_ANAL_ESIL_PARM_REG ; 
 int /*<<< orphan*/ * _edf_origin_reg_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * _edf_reg_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  _edf_reg_set (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _edf_var_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* r_anal_esil_dfg_node_new (TYPE_2__*,char*) ; 
 void* r_anal_esil_get_parm_type (TYPE_3__*,char*) ; 
 char* r_anal_esil_pop (TYPE_3__*) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_graph_add_node (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static bool _edf_consume_2_set_reg(RAnalEsil *esil, const bool use_origin) {
	const char *op_string = esil->current_opstr;
	RAnalEsilDFG *edf = (RAnalEsilDFG *)esil->user;
	char *dst = r_anal_esil_pop (esil);
	char *src = r_anal_esil_pop (esil);

	if (!src || !dst) {
		free (dst);
		free (src);
		return false;
	}

	int dst_type = r_anal_esil_get_parm_type (esil, dst);
	if (dst_type == R_ANAL_ESIL_PARM_INVALID) {
		free (dst);
		free (src);
		return false;
	}

	const int src_type = r_anal_esil_get_parm_type (esil, src);
	RGraphNode *src_node = NULL;
	if (src_type == R_ANAL_ESIL_PARM_REG) {
		src_node = _edf_reg_get (edf, src);
	} else if (src_type == R_ANAL_ESIL_PARM_NUM) {
		RGraphNode *n_value = r_graph_add_node (edf->flow, r_anal_esil_dfg_node_new (edf, src));
		RAnalEsilDFGNode *ec_node = r_anal_esil_dfg_node_new (edf, src);
		ec_node->type = R_ANAL_ESIL_DFG_BLOCK_CONST;
		r_strbuf_appendf (ec_node->content, ":const_%d", edf->idx++);
		src_node = r_graph_add_node (edf->flow, ec_node);
		r_graph_add_edge (edf->flow, n_value, src_node);
	} else {
		src_node = _edf_var_get (edf, src);
	}

	RGraphNode *dst_node = use_origin ? _edf_origin_reg_get (edf, dst) : _edf_reg_get (edf, dst);
	RGraphNode *old_dst_node = dst_node;

	if (!src_node || !dst_node) {
		free (src);
		free (dst);
		return false;
	}

	RAnalEsilDFGNode *eop_node = r_anal_esil_dfg_node_new (edf, src);
	r_strbuf_appendf (eop_node->content, ",%s,%s", dst, op_string);
	eop_node->type = R_ANAL_ESIL_DFG_BLOCK_GENERATIVE;
	free (src);

	RGraphNode *op_node = r_graph_add_node (edf->flow, eop_node);
	r_graph_add_edge (edf->flow, dst_node, op_node);
	r_graph_add_edge (edf->flow, src_node, op_node);
	edf->old = old_dst_node;
	RAnalEsilDFGNode *result = r_anal_esil_dfg_node_new (edf, dst);
	result->type = R_ANAL_ESIL_DFG_BLOCK_RESULT | R_ANAL_ESIL_DFG_BLOCK_VAR;

	r_strbuf_appendf (result->content, ":var_%d", edf->idx++);
	dst_node = r_graph_add_node (edf->flow, result);
	r_graph_add_edge (edf->flow, op_node, dst_node);
	_edf_reg_set (edf, dst, dst_node);
	edf->cur = dst_node;
	free (dst);
	return true;
}