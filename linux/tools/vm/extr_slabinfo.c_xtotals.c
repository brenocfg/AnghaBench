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

/* Variables and functions */
 int /*<<< orphan*/  _xtotals (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  link_slabs () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rename_slabs () ; 
 int /*<<< orphan*/  totals () ; 

__attribute__((used)) static void xtotals(void)
{
	char *heading, *underline;

	totals();

	link_slabs();
	rename_slabs();

	heading = "\nSlabs sorted by size\n";
	underline = "--------------------\n";
	_xtotals(heading, underline, 0, 1, 0);

	heading = "\nSlabs sorted by loss\n";
	underline = "--------------------\n";
	_xtotals(heading, underline, 1, 0, 0);

	heading = "\nSlabs sorted by number of partial slabs\n";
	underline = "---------------------------------------\n";
	_xtotals(heading, underline, 0, 0, 1);

	printf("\n");
}