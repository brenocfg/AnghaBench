#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ init_called; scalar_t__ acpi_driver_registered; scalar_t__ proc_created; scalar_t__ acpi_notify_installed; } ;
struct ibm_struct {int /*<<< orphan*/  name; TYPE_2__ flags; int /*<<< orphan*/  (* exit ) () ;TYPE_1__* acpi; int /*<<< orphan*/  all_drivers; } ;
struct TYPE_3__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  type; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  TPACPI_DBG_EXIT ; 
 int /*<<< orphan*/  TPACPI_DBG_INIT ; 
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispatch_acpi_notify ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_dir ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void ibm_exit(struct ibm_struct *ibm)
{
	dbg_printk(TPACPI_DBG_EXIT, "removing %s\n", ibm->name);

	list_del_init(&ibm->all_drivers);

	if (ibm->flags.acpi_notify_installed) {
		dbg_printk(TPACPI_DBG_EXIT,
			"%s: acpi_remove_notify_handler\n", ibm->name);
		BUG_ON(!ibm->acpi);
		acpi_remove_notify_handler(*ibm->acpi->handle,
					   ibm->acpi->type,
					   dispatch_acpi_notify);
		ibm->flags.acpi_notify_installed = 0;
	}

	if (ibm->flags.proc_created) {
		dbg_printk(TPACPI_DBG_EXIT,
			"%s: remove_proc_entry\n", ibm->name);
		remove_proc_entry(ibm->name, proc_dir);
		ibm->flags.proc_created = 0;
	}

	if (ibm->flags.acpi_driver_registered) {
		dbg_printk(TPACPI_DBG_EXIT,
			"%s: acpi_bus_unregister_driver\n", ibm->name);
		BUG_ON(!ibm->acpi);
		acpi_bus_unregister_driver(ibm->acpi->driver);
		kfree(ibm->acpi->driver);
		ibm->acpi->driver = NULL;
		ibm->flags.acpi_driver_registered = 0;
	}

	if (ibm->flags.init_called && ibm->exit) {
		ibm->exit();
		ibm->flags.init_called = 0;
	}

	dbg_printk(TPACPI_DBG_INIT, "finished removing %s\n", ibm->name);
}