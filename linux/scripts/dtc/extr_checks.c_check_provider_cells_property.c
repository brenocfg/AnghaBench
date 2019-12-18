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
struct provider {int /*<<< orphan*/  prop_name; } ;
struct property {int dummy; } ;
struct node {int dummy; } ;
struct dt_info {int dummy; } ;
struct check {struct provider* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_property_phandle_args (struct check*,struct dt_info*,struct node*,struct property*,struct provider*) ; 
 struct property* get_property (struct node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_provider_cells_property(struct check *c,
					  struct dt_info *dti,
				          struct node *node)
{
	struct provider *provider = c->data;
	struct property *prop;

	prop = get_property(node, provider->prop_name);
	if (!prop)
		return;

	check_property_phandle_args(c, dti, node, prop, provider);
}