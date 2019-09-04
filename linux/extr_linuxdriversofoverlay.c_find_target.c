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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char const*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,...) ; 

__attribute__((used)) static struct device_node *find_target(struct device_node *info_node)
{
	struct device_node *node;
	const char *path;
	u32 val;
	int ret;

	ret = of_property_read_u32(info_node, "target", &val);
	if (!ret) {
		node = of_find_node_by_phandle(val);
		if (!node)
			pr_err("find target, node: %pOF, phandle 0x%x not found\n",
			       info_node, val);
		return node;
	}

	ret = of_property_read_string(info_node, "target-path", &path);
	if (!ret) {
		node =  of_find_node_by_path(path);
		if (!node)
			pr_err("find target, node: %pOF, path '%s' not found\n",
			       info_node, path);
		return node;
	}

	pr_err("find target, node: %pOF, no target property\n", info_node);

	return NULL;
}