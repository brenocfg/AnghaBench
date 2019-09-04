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
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_children_props(struct device_node *dn, const int **drc_indexes,
		const int **drc_names, const int **drc_types,
		const int **drc_power_domains)
{
	const int *indexes, *names, *types, *domains;

	indexes = of_get_property(dn, "ibm,drc-indexes", NULL);
	names = of_get_property(dn, "ibm,drc-names", NULL);
	types = of_get_property(dn, "ibm,drc-types", NULL);
	domains = of_get_property(dn, "ibm,drc-power-domains", NULL);

	if (!indexes || !names || !types || !domains) {
		/* Slot does not have dynamically-removable children */
		return -EINVAL;
	}
	if (drc_indexes)
		*drc_indexes = indexes;
	if (drc_names)
		/* &drc_names[1] contains NULL terminated slot names */
		*drc_names = names;
	if (drc_types)
		/* &drc_types[1] contains NULL terminated slot types */
		*drc_types = types;
	if (drc_power_domains)
		*drc_power_domains = domains;

	return 0;
}