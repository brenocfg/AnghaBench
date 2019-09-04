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
struct pnv_php_slot {int /*<<< orphan*/  state; int /*<<< orphan*/  link; int /*<<< orphan*/  children; struct pnv_php_slot* parent; int /*<<< orphan*/  pdev; int /*<<< orphan*/  name; int /*<<< orphan*/  slot_no; int /*<<< orphan*/  bus; int /*<<< orphan*/  slot; struct device_node* dn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  PNV_PHP_STATE_REGISTERED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int pci_hp_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct pnv_php_slot* pnv_php_find_slot (struct device_node*) ; 
 int /*<<< orphan*/  pnv_php_lock ; 
 int /*<<< orphan*/  pnv_php_put_slot (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  pnv_php_slot_list ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pnv_php_register_slot(struct pnv_php_slot *php_slot)
{
	struct pnv_php_slot *parent;
	struct device_node *dn = php_slot->dn;
	unsigned long flags;
	int ret;

	/* Check if the slot is registered or not */
	parent = pnv_php_find_slot(php_slot->dn);
	if (parent) {
		pnv_php_put_slot(parent);
		return -EEXIST;
	}

	/* Register PCI slot */
	ret = pci_hp_register(&php_slot->slot, php_slot->bus,
			      php_slot->slot_no, php_slot->name);
	if (ret) {
		pci_warn(php_slot->pdev, "Error %d registering slot\n", ret);
		return ret;
	}

	/* Attach to the parent's child list or global list */
	while ((dn = of_get_parent(dn))) {
		if (!PCI_DN(dn)) {
			of_node_put(dn);
			break;
		}

		parent = pnv_php_find_slot(dn);
		if (parent) {
			of_node_put(dn);
			break;
		}

		of_node_put(dn);
	}

	spin_lock_irqsave(&pnv_php_lock, flags);
	php_slot->parent = parent;
	if (parent)
		list_add_tail(&php_slot->link, &parent->children);
	else
		list_add_tail(&php_slot->link, &pnv_php_slot_list);
	spin_unlock_irqrestore(&pnv_php_lock, flags);

	php_slot->state = PNV_PHP_STATE_REGISTERED;
	return 0;
}