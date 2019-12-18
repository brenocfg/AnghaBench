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
typedef  int /*<<< orphan*/  pairingheap_node ;
struct TYPE_4__ {int /*<<< orphan*/ * ph_root; } ;
typedef  TYPE_1__ pairingheap ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  pairingheap_is_empty (TYPE_1__*) ; 

pairingheap_node *
pairingheap_first(pairingheap *heap)
{
	Assert(!pairingheap_is_empty(heap));

	return heap->ph_root;
}