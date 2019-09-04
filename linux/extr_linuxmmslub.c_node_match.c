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

__attribute__((used)) static inline int node_match(struct page *page, int node)
{
#ifdef CONFIG_NUMA
	if (!page || (node != NUMA_NO_NODE && page_to_nid(page) != node))
		return 0;
#endif
	return 1;
}