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
struct zone {unsigned int spanned_pages; } ;
struct rtree_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_BITS_PER_BLOCK ; 
 int /*<<< orphan*/  BM_ENTRIES_PER_LEVEL ; 
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINKED_PAGE_DATA_SIZE ; 

unsigned int snapshot_additional_pages(struct zone *zone)
{
	unsigned int rtree, nodes;

	rtree = nodes = DIV_ROUND_UP(zone->spanned_pages, BM_BITS_PER_BLOCK);
	rtree += DIV_ROUND_UP(rtree * sizeof(struct rtree_node),
			      LINKED_PAGE_DATA_SIZE);
	while (nodes > 1) {
		nodes = DIV_ROUND_UP(nodes, BM_ENTRIES_PER_LEVEL);
		rtree += nodes;
	}

	return 2 * rtree;
}