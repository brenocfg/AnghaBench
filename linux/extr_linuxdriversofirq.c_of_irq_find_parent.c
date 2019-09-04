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
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int OF_IMAP_NO_PHANDLE ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_irq_dflt_pic ; 
 int of_irq_workarounds ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

struct device_node *of_irq_find_parent(struct device_node *child)
{
	struct device_node *p;
	phandle parent;

	if (!of_node_get(child))
		return NULL;

	do {
		if (of_property_read_u32(child, "interrupt-parent", &parent)) {
			p = of_get_parent(child);
		} else	{
			if (of_irq_workarounds & OF_IMAP_NO_PHANDLE)
				p = of_node_get(of_irq_dflt_pic);
			else
				p = of_find_node_by_phandle(parent);
		}
		of_node_put(child);
		child = p;
	} while (p && of_get_property(p, "#interrupt-cells", NULL) == NULL);

	return p;
}