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
typedef  int /*<<< orphan*/  grand_totals ;
struct TYPE_4__ {scalar_t__ freespace; scalar_t__ totalspace; int /*<<< orphan*/  freechunks; int /*<<< orphan*/  nblocks; } ;
typedef  TYPE_1__ MemoryContextCounters ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextStatsInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

void
MemoryContextStatsDetail(MemoryContext context, int max_children)
{
	MemoryContextCounters grand_totals;

	memset(&grand_totals, 0, sizeof(grand_totals));

	MemoryContextStatsInternal(context, 0, true, max_children, &grand_totals);

	fprintf(stderr,
			"Grand total: %zu bytes in %zd blocks; %zu free (%zd chunks); %zu used\n",
			grand_totals.totalspace, grand_totals.nblocks,
			grand_totals.freespace, grand_totals.freechunks,
			grand_totals.totalspace - grand_totals.freespace);
}