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
 scalar_t__ line ; 
 int /*<<< orphan*/  link_slabs () ; 
 int /*<<< orphan*/  output_slabs () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rename_slabs () ; 
 int sort_loss ; 
 int sort_size ; 
 int /*<<< orphan*/  sort_slabs () ; 
 int /*<<< orphan*/  totals () ; 

__attribute__((used)) static void xtotals(void)
{
	totals();

	link_slabs();
	rename_slabs();

	printf("\nSlabs sorted by size\n");
	printf("--------------------\n");
	sort_loss = 0;
	sort_size = 1;
	sort_slabs();
	output_slabs();

	printf("\nSlabs sorted by loss\n");
	printf("--------------------\n");
	line = 0;
	sort_loss = 1;
	sort_size = 0;
	sort_slabs();
	output_slabs();
	printf("\n");
}