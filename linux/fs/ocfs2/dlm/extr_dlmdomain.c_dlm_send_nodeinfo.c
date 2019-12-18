#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct o2nm_node {int /*<<< orphan*/  nd_ipv4_port; int /*<<< orphan*/  nd_ipv4_address; int /*<<< orphan*/  nd_num; } ;
struct dlm_query_nodeinfo {int qn_nodenum; int qn_numnodes; int /*<<< orphan*/  qn_namelen; int /*<<< orphan*/  qn_domain; TYPE_1__* qn_nodes; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  ni_ipv4_address; int /*<<< orphan*/  ni_ipv4_port; int /*<<< orphan*/  ni_nodenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MOD_KEY ; 
 int /*<<< orphan*/  DLM_QUERY_NODEINFO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int O2NM_MAX_NODES ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  kfree (struct dlm_query_nodeinfo*) ; 
 struct dlm_query_nodeinfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_query_nodeinfo*,int,int,int*) ; 
 struct o2nm_node* o2nm_get_node_by_num (int) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_send_nodeinfo(struct dlm_ctxt *dlm, unsigned long *node_map)
{
	struct dlm_query_nodeinfo *qn = NULL;
	struct o2nm_node *node;
	int ret = 0, status, count, i;

	if (find_next_bit(node_map, O2NM_MAX_NODES, 0) >= O2NM_MAX_NODES)
		goto bail;

	qn = kzalloc(sizeof(struct dlm_query_nodeinfo), GFP_KERNEL);
	if (!qn) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto bail;
	}

	for (i = 0, count = 0; i < O2NM_MAX_NODES; ++i) {
		node = o2nm_get_node_by_num(i);
		if (!node)
			continue;
		qn->qn_nodes[count].ni_nodenum = node->nd_num;
		qn->qn_nodes[count].ni_ipv4_port = node->nd_ipv4_port;
		qn->qn_nodes[count].ni_ipv4_address = node->nd_ipv4_address;
		mlog(0, "Node %3d, %pI4:%u\n", node->nd_num,
		     &(node->nd_ipv4_address), ntohs(node->nd_ipv4_port));
		++count;
		o2nm_node_put(node);
	}

	qn->qn_nodenum = dlm->node_num;
	qn->qn_numnodes = count;
	qn->qn_namelen = strlen(dlm->name);
	memcpy(qn->qn_domain, dlm->name, qn->qn_namelen);

	i = -1;
	while ((i = find_next_bit(node_map, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) {
		if (i == dlm->node_num)
			continue;

		mlog(0, "Sending nodeinfo to node %d\n", i);

		ret = o2net_send_message(DLM_QUERY_NODEINFO, DLM_MOD_KEY,
					 qn, sizeof(struct dlm_query_nodeinfo),
					 i, &status);
		if (ret >= 0)
			ret = status;
		if (ret) {
			mlog(ML_ERROR, "node mismatch %d, node %d\n", ret, i);
			break;
		}
	}

bail:
	kfree(qn);
	return ret;
}