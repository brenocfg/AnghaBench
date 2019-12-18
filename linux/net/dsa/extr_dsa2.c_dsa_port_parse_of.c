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
struct net_device {int dummy; } ;
struct dsa_port {struct device_node* dn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int dsa_port_parse_cpu (struct dsa_port*,struct net_device*) ; 
 int dsa_port_parse_dsa (struct dsa_port*) ; 
 int dsa_port_parse_user (struct dsa_port*,char const*) ; 
 struct net_device* of_find_net_device_by_node (struct device_node*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int dsa_port_parse_of(struct dsa_port *dp, struct device_node *dn)
{
	struct device_node *ethernet = of_parse_phandle(dn, "ethernet", 0);
	const char *name = of_get_property(dn, "label", NULL);
	bool link = of_property_read_bool(dn, "link");

	dp->dn = dn;

	if (ethernet) {
		struct net_device *master;

		master = of_find_net_device_by_node(ethernet);
		if (!master)
			return -EPROBE_DEFER;

		return dsa_port_parse_cpu(dp, master);
	}

	if (link)
		return dsa_port_parse_dsa(dp);

	return dsa_port_parse_user(dp, name);
}