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
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; struct device_node* np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_simple_card_get_dai_id (struct device_node*) ; 
 int of_graph_get_endpoint_count (struct device_node*) ; 
 struct device_node* of_graph_get_port_parent (struct device_node*) ; 
 int snd_soc_get_dai_name (struct of_phandle_args*,char const**) ; 

int asoc_simple_card_parse_graph_dai(struct device_node *ep,
				     struct device_node **dai_of_node,
				     const char **dai_name)
{
	struct device_node *node;
	struct of_phandle_args args;
	int ret;

	if (!ep)
		return 0;
	if (!dai_name)
		return 0;

	node = of_graph_get_port_parent(ep);

	/* Get dai->name */
	args.np		= node;
	args.args[0]	= asoc_simple_card_get_dai_id(ep);
	args.args_count	= (of_graph_get_endpoint_count(node) > 1);

	ret = snd_soc_get_dai_name(&args, dai_name);
	if (ret < 0)
		return ret;

	*dai_of_node = node;

	return 0;
}