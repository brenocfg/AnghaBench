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
struct page {int dummy; } ;

/* Variables and functions */
 size_t N_MEMORY ; 
 struct page* new_page_nodemask (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * node_states ; 
 int /*<<< orphan*/  numa_node_id () ; 

struct page *alloc_migrate_target(struct page *page, unsigned long private)
{
	return new_page_nodemask(page, numa_node_id(), &node_states[N_MEMORY]);
}