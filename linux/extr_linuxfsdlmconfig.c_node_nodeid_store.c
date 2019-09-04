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
typedef  int /*<<< orphan*/  uint32_t ;
struct dlm_node {int /*<<< orphan*/  comm_seq; int /*<<< orphan*/  nodeid; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct dlm_node* config_item_to_node (struct config_item*) ; 
 int /*<<< orphan*/  dlm_comm_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t node_nodeid_store(struct config_item *item, const char *buf,
				 size_t len)
{
	struct dlm_node *nd = config_item_to_node(item);
	uint32_t seq = 0;
	int rc = kstrtoint(buf, 0, &nd->nodeid);

	if (rc)
		return rc;
	dlm_comm_seq(nd->nodeid, &seq);
	nd->comm_seq = seq;
	return len;
}