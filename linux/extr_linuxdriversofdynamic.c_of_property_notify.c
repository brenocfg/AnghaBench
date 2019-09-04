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
struct property {int dummy; } ;
struct of_reconfig_data {struct property* old_prop; struct property* prop; struct device_node* dn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_is_attached (struct device_node*) ; 
 int of_reconfig_notify (int,struct of_reconfig_data*) ; 

int of_property_notify(int action, struct device_node *np,
		       struct property *prop, struct property *oldprop)
{
	struct of_reconfig_data pr;

	/* only call notifiers if the node is attached */
	if (!of_node_is_attached(np))
		return 0;

	pr.dn = np;
	pr.prop = prop;
	pr.old_prop = oldprop;
	return of_reconfig_notify(action, &pr);
}