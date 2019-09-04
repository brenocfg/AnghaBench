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
struct pnv_php_slot {int /*<<< orphan*/  slot; int /*<<< orphan*/  state; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNV_PHP_STATE_OFFLINE ; 
 int /*<<< orphan*/  pci_hp_deregister (int /*<<< orphan*/ *) ; 
 struct pnv_php_slot* pnv_php_find_slot (struct device_node*) ; 
 int /*<<< orphan*/  pnv_php_put_slot (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  pnv_php_release (struct pnv_php_slot*) ; 

__attribute__((used)) static void pnv_php_unregister_one(struct device_node *dn)
{
	struct pnv_php_slot *php_slot;

	php_slot = pnv_php_find_slot(dn);
	if (!php_slot)
		return;

	php_slot->state = PNV_PHP_STATE_OFFLINE;
	pci_hp_deregister(&php_slot->slot);
	pnv_php_release(php_slot);
	pnv_php_put_slot(php_slot);
}