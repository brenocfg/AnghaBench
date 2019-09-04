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
struct gasket_page_table {int /*<<< orphan*/  device; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  gasket_page_table_garbage_collect (struct gasket_page_table*) ; 
 int /*<<< orphan*/  kfree (struct gasket_page_table*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void gasket_page_table_cleanup(struct gasket_page_table *pg_tbl)
{
	/* Deallocate free second-level tables. */
	gasket_page_table_garbage_collect(pg_tbl);

	/* TODO: Check that all PTEs have been freed? */

	vfree(pg_tbl->entries);
	pg_tbl->entries = NULL;

	put_device(pg_tbl->device);
	kfree(pg_tbl);
}