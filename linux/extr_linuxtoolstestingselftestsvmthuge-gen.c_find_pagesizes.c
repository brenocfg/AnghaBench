#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int gl_pathc; int /*<<< orphan*/ * gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int NUM_PAGESIZES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int num_page_sizes ; 
 int* page_sizes ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 

void find_pagesizes(void)
{
	glob_t g;
	int i;
	glob("/sys/kernel/mm/hugepages/hugepages-*kB", 0, NULL, &g);
	assert(g.gl_pathc <= NUM_PAGESIZES);
	for (i = 0; i < g.gl_pathc; i++) {
		sscanf(g.gl_pathv[i], "/sys/kernel/mm/hugepages/hugepages-%lukB",
				&page_sizes[i]);
		page_sizes[i] <<= 10;
		printf("Found %luMB\n", page_sizes[i] >> 20);
	}
	num_page_sizes = g.gl_pathc;
	globfree(&g);
}