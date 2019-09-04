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
typedef  scalar_t__ u32 ;
struct pnv_php_slot {int /*<<< orphan*/  dn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct pnv_php_slot* pnv_php_alloc_slot (struct device_node*) ; 
 int pnv_php_enable (struct pnv_php_slot*,int) ; 
 int /*<<< orphan*/  pnv_php_enable_irq (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  pnv_php_put_slot (struct pnv_php_slot*) ; 
 int pnv_php_register_slot (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  pnv_php_unregister_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnv_php_register_one(struct device_node *dn)
{
	struct pnv_php_slot *php_slot;
	u32 prop32;
	int ret;

	/* Check if it's hotpluggable slot */
	ret = of_property_read_u32(dn, "ibm,slot-pluggable", &prop32);
	if (ret || !prop32)
		return -ENXIO;

	ret = of_property_read_u32(dn, "ibm,reset-by-firmware", &prop32);
	if (ret || !prop32)
		return -ENXIO;

	php_slot = pnv_php_alloc_slot(dn);
	if (!php_slot)
		return -ENODEV;

	ret = pnv_php_register_slot(php_slot);
	if (ret)
		goto free_slot;

	ret = pnv_php_enable(php_slot, false);
	if (ret)
		goto unregister_slot;

	/* Enable interrupt if the slot supports surprise hotplug */
	ret = of_property_read_u32(dn, "ibm,slot-surprise-pluggable", &prop32);
	if (!ret && prop32)
		pnv_php_enable_irq(php_slot);

	return 0;

unregister_slot:
	pnv_php_unregister_one(php_slot->dn);
free_slot:
	pnv_php_put_slot(php_slot);
	return ret;
}