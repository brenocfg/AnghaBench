#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* first_child; struct TYPE_9__* next_sibling; struct TYPE_9__* prev_or_parent; } ;
typedef  TYPE_1__ pairingheap_node ;
struct TYPE_10__ {scalar_t__ (* ph_compare ) (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ph_arg; } ;
typedef  TYPE_2__ pairingheap ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pairingheap_node *
merge(pairingheap *heap, pairingheap_node *a, pairingheap_node *b)
{
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	/* swap 'a' and 'b' so that 'a' is the one with larger value */
	if (heap->ph_compare(a, b, heap->ph_arg) < 0)
	{
		pairingheap_node *tmp;

		tmp = a;
		a = b;
		b = tmp;
	}

	/* and put 'b' as a child of 'a' */
	if (a->first_child)
		a->first_child->prev_or_parent = b;
	b->prev_or_parent = a;
	b->next_sibling = a->first_child;
	a->first_child = b;

	return a;
}