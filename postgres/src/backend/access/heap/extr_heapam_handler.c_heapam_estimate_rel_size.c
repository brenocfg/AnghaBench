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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_OVERHEAD_BYTES_PER_TUPLE ; 
 int /*<<< orphan*/  HEAP_USABLE_BYTES_PER_PAGE ; 
 int /*<<< orphan*/  table_block_relation_estimate_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
heapam_estimate_rel_size(Relation rel, int32 *attr_widths,
						 BlockNumber *pages, double *tuples,
						 double *allvisfrac)
{
	table_block_relation_estimate_size(rel, attr_widths, pages,
									   tuples, allvisfrac,
									   HEAP_OVERHEAD_BYTES_PER_TUPLE,
									   HEAP_USABLE_BYTES_PER_PAGE);
}