#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * bh_nodes; } ;
typedef  TYPE_1__ binaryheap ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */

__attribute__((used)) static inline void
swap_nodes(binaryheap *heap, int a, int b)
{
	Datum		swap;

	swap = heap->bh_nodes[a];
	heap->bh_nodes[a] = heap->bh_nodes[b];
	heap->bh_nodes[b] = swap;
}