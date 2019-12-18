#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathGinPath ;
typedef  int /*<<< orphan*/  JsonPathGinNode ;
typedef  int /*<<< orphan*/  JsonPathGinContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSP_GIN_AND ; 
 int /*<<< orphan*/ * extract_jsp_path_expr_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_jsp_expr_node_args (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonPathGinNode *
extract_jsp_path_expr(JsonPathGinContext *cxt, JsonPathGinPath path,
					  JsonPathItem *jsp, JsonbValue *scalar)
{
	/* extract a list of nodes to be AND-ed */
	List	   *nodes = extract_jsp_path_expr_nodes(cxt, path, jsp, scalar);

	if (list_length(nodes) <= 0)
		/* no nodes were extracted => full scan is needed for this path */
		return NULL;

	if (list_length(nodes) == 1)
		return linitial(nodes); /* avoid extra AND-node */

	/* construct AND-node for path with filters */
	return make_jsp_expr_node_args(JSP_GIN_AND, nodes);
}