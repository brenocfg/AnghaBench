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
struct gasket_page_table {int num_extended_entries; int /*<<< orphan*/  num_simple_entries; } ;

/* Variables and functions */
 int GASKET_PAGES_PER_SUBTABLE ; 
 int /*<<< orphan*/  gasket_components_to_dev_address (struct gasket_page_table*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_unmap_extended_pages (struct gasket_page_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gasket_unmap_simple_pages (struct gasket_page_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gasket_page_table_unmap_all_nolock(struct gasket_page_table *pg_tbl)
{
	gasket_unmap_simple_pages(pg_tbl,
				  gasket_components_to_dev_address(pg_tbl, 1, 0,
								   0),
				  pg_tbl->num_simple_entries);
	gasket_unmap_extended_pages(pg_tbl,
				    gasket_components_to_dev_address(pg_tbl, 0,
								     0, 0),
				    pg_tbl->num_extended_entries *
				    GASKET_PAGES_PER_SUBTABLE);
}