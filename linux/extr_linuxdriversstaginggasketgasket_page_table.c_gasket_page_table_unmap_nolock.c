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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  uint ;
struct gasket_page_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ gasket_addr_is_simple (struct gasket_page_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_unmap_extended_pages (struct gasket_page_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_unmap_simple_pages (struct gasket_page_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gasket_page_table_unmap_nolock(struct gasket_page_table *pg_tbl,
					   ulong dev_addr, uint num_pages)
{
	if (!num_pages)
		return;

	if (gasket_addr_is_simple(pg_tbl, dev_addr))
		gasket_unmap_simple_pages(pg_tbl, dev_addr, num_pages);
	else
		gasket_unmap_extended_pages(pg_tbl, dev_addr, num_pages);
}