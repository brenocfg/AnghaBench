#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct TYPE_2__ {int /*<<< orphan*/  total_entries; } ;
struct gasket_page_table {TYPE_1__ config; } ;

/* Variables and functions */

uint gasket_page_table_max_size(struct gasket_page_table *page_table)
{
	if (!page_table)
		return 0;
	return page_table->config.total_entries;
}