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
typedef  int /*<<< orphan*/  pairingheap_comparator ;
struct TYPE_3__ {int /*<<< orphan*/ * ph_root; void* ph_arg; int /*<<< orphan*/  ph_compare; } ;
typedef  TYPE_1__ pairingheap ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

pairingheap *
pairingheap_allocate(pairingheap_comparator compare, void *arg)
{
	pairingheap *heap;

	heap = (pairingheap *) palloc(sizeof(pairingheap));
	heap->ph_compare = compare;
	heap->ph_arg = arg;

	heap->ph_root = NULL;

	return heap;
}