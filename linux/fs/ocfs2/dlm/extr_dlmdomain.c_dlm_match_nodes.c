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
struct o2nm_node {int nd_num; scalar_t__ nd_ipv4_port; scalar_t__ nd_ipv4_address; } ;
struct dlm_query_nodeinfo {int qn_numnodes; int /*<<< orphan*/  qn_nodenum; int /*<<< orphan*/  qn_domain; struct dlm_node_info* qn_nodes; } ;
struct dlm_node_info {int ni_nodenum; scalar_t__ ni_ipv4_address; scalar_t__ ni_ipv4_port; } ;
struct dlm_ctxt {int /*<<< orphan*/  node_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 struct o2nm_node* o2nm_get_node_by_num (int) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 

__attribute__((used)) static int dlm_match_nodes(struct dlm_ctxt *dlm, struct dlm_query_nodeinfo *qn)
{
	struct o2nm_node *local;
	struct dlm_node_info *remote;
	int i, j;
	int status = 0;

	for (j = 0; j < qn->qn_numnodes; ++j)
		mlog(0, "Node %3d, %pI4:%u\n", qn->qn_nodes[j].ni_nodenum,
		     &(qn->qn_nodes[j].ni_ipv4_address),
		     ntohs(qn->qn_nodes[j].ni_ipv4_port));

	for (i = 0; i < O2NM_MAX_NODES && !status; ++i) {
		local = o2nm_get_node_by_num(i);
		remote = NULL;
		for (j = 0; j < qn->qn_numnodes; ++j) {
			if (qn->qn_nodes[j].ni_nodenum == i) {
				remote = &(qn->qn_nodes[j]);
				break;
			}
		}

		if (!local && !remote)
			continue;

		if ((local && !remote) || (!local && remote))
			status = -EINVAL;

		if (!status &&
		    ((remote->ni_nodenum != local->nd_num) ||
		     (remote->ni_ipv4_port != local->nd_ipv4_port) ||
		     (remote->ni_ipv4_address != local->nd_ipv4_address)))
			status = -EINVAL;

		if (status) {
			if (remote && !local)
				mlog(ML_ERROR, "Domain %s: Node %d (%pI4:%u) "
				     "registered in joining node %d but not in "
				     "local node %d\n", qn->qn_domain,
				     remote->ni_nodenum,
				     &(remote->ni_ipv4_address),
				     ntohs(remote->ni_ipv4_port),
				     qn->qn_nodenum, dlm->node_num);
			if (local && !remote)
				mlog(ML_ERROR, "Domain %s: Node %d (%pI4:%u) "
				     "registered in local node %d but not in "
				     "joining node %d\n", qn->qn_domain,
				     local->nd_num, &(local->nd_ipv4_address),
				     ntohs(local->nd_ipv4_port),
				     dlm->node_num, qn->qn_nodenum);
			BUG_ON((!local && !remote));
		}

		if (local)
			o2nm_node_put(local);
	}

	return status;
}