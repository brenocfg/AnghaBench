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
typedef  scalar_t__ ulong ;
typedef  scalar_t__ u64 ;
struct gasket_page_table {int num_coherent_pages; TYPE_1__* coherent_pages; } ;
struct TYPE_2__ {scalar_t__ user_virt; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static int is_coherent(struct gasket_page_table *pg_tbl, ulong host_addr)
{
	u64 min, max;

	/* whether the host address is within user virt range */
	if (!pg_tbl->coherent_pages)
		return 0;

	min = (u64)pg_tbl->coherent_pages[0].user_virt;
	max = min + PAGE_SIZE * pg_tbl->num_coherent_pages;

	return min <= host_addr && host_addr < max;
}