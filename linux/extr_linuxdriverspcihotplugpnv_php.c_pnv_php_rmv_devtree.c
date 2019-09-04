#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnv_php_slot {int /*<<< orphan*/ * fdt; TYPE_1__* dn; int /*<<< orphan*/ * dt; int /*<<< orphan*/  ocs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_changeset_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnv_php_detach_device_nodes (TYPE_1__*) ; 
 int /*<<< orphan*/  pnv_php_rmv_pdns (TYPE_1__*) ; 

__attribute__((used)) static void pnv_php_rmv_devtree(struct pnv_php_slot *php_slot)
{
	pnv_php_rmv_pdns(php_slot->dn);

	/*
	 * Decrease the refcount if the device nodes were created
	 * through OF changeset before detaching them.
	 */
	if (php_slot->fdt)
		of_changeset_destroy(&php_slot->ocs);
	pnv_php_detach_device_nodes(php_slot->dn);

	if (php_slot->fdt) {
		kfree(php_slot->dt);
		kfree(php_slot->fdt);
		php_slot->dt        = NULL;
		php_slot->dn->child = NULL;
		php_slot->fdt       = NULL;
	}
}