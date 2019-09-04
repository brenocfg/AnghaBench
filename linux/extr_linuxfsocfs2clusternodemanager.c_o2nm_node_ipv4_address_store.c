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
struct rb_node {int dummy; } ;
struct o2nm_node {int /*<<< orphan*/  nd_ipv4_address; int /*<<< orphan*/  nd_ip_node; int /*<<< orphan*/  nd_set_attributes; } ;
struct o2nm_cluster {int /*<<< orphan*/  cl_nodes_lock; int /*<<< orphan*/  cl_node_ip_tree; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ipv4_addr ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  O2NM_NODE_ATTR_ADDRESS ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  o2nm_lock_subsystem () ; 
 scalar_t__ o2nm_node_ip_tree_lookup (struct o2nm_cluster*,int /*<<< orphan*/ ,struct rb_node***,struct rb_node**) ; 
 int /*<<< orphan*/  o2nm_unlock_subsystem () ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct o2nm_cluster* to_o2nm_cluster_from_node (struct o2nm_node*) ; 
 struct o2nm_node* to_o2nm_node (struct config_item*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t o2nm_node_ipv4_address_store(struct config_item *item,
					    const char *page,
					    size_t count)
{
	struct o2nm_node *node = to_o2nm_node(item);
	struct o2nm_cluster *cluster;
	int ret, i;
	struct rb_node **p, *parent;
	unsigned int octets[4];
	__be32 ipv4_addr = 0;

	ret = sscanf(page, "%3u.%3u.%3u.%3u", &octets[3], &octets[2],
		     &octets[1], &octets[0]);
	if (ret != 4)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(octets); i++) {
		if (octets[i] > 255)
			return -ERANGE;
		be32_add_cpu(&ipv4_addr, octets[i] << (i * 8));
	}

	o2nm_lock_subsystem();
	cluster = to_o2nm_cluster_from_node(node);
	if (!cluster) {
		o2nm_unlock_subsystem();
		return -EINVAL;
	}

	ret = 0;
	write_lock(&cluster->cl_nodes_lock);
	if (o2nm_node_ip_tree_lookup(cluster, ipv4_addr, &p, &parent))
		ret = -EEXIST;
	else if (test_and_set_bit(O2NM_NODE_ATTR_ADDRESS,
			&node->nd_set_attributes))
		ret = -EBUSY;
	else {
		rb_link_node(&node->nd_ip_node, parent, p);
		rb_insert_color(&node->nd_ip_node, &cluster->cl_node_ip_tree);
	}
	write_unlock(&cluster->cl_nodes_lock);
	o2nm_unlock_subsystem();

	if (ret)
		return ret;

	memcpy(&node->nd_ipv4_address, &ipv4_addr, sizeof(ipv4_addr));

	return count;
}