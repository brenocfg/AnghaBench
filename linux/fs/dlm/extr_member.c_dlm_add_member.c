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
struct dlm_member {int /*<<< orphan*/  comm_seq; int /*<<< orphan*/  weight; int /*<<< orphan*/  nodeid; } ;
struct dlm_ls {int /*<<< orphan*/  ls_num_nodes; } ;
struct dlm_config_node {int /*<<< orphan*/  comm_seq; int /*<<< orphan*/  weight; int /*<<< orphan*/  nodeid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  add_ordered_member (struct dlm_ls*,struct dlm_member*) ; 
 int dlm_lowcomms_connect_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dlm_member*) ; 
 struct dlm_member* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_add_member(struct dlm_ls *ls, struct dlm_config_node *node)
{
	struct dlm_member *memb;
	int error;

	memb = kzalloc(sizeof(*memb), GFP_NOFS);
	if (!memb)
		return -ENOMEM;

	error = dlm_lowcomms_connect_node(node->nodeid);
	if (error < 0) {
		kfree(memb);
		return error;
	}

	memb->nodeid = node->nodeid;
	memb->weight = node->weight;
	memb->comm_seq = node->comm_seq;
	add_ordered_member(ls, memb);
	ls->ls_num_nodes++;
	return 0;
}