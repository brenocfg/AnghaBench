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
struct sparsebit {scalar_t__ num_set; TYPE_1__* root; } ;
typedef  scalar_t__ sparsebit_num_t ;
typedef  int /*<<< orphan*/  mask_t ;
struct TYPE_2__ {scalar_t__ num_after; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ MASK_BITS ; 
 int /*<<< orphan*/  assert (int) ; 

bool sparsebit_any_set(struct sparsebit *s)
{
	/*
	 * Nodes only describe set bits.  If any nodes then there
	 * is at least 1 bit set.
	 */
	if (!s->root)
		return false;

	/*
	 * Every node should have a non-zero mask.  For now will
	 * just assure that the root node has a non-zero mask,
	 * which is a quick check that at least 1 bit is set.
	 */
	assert(s->root->mask != 0);
	assert(s->num_set > 0 ||
	       (s->root->num_after == ((sparsebit_num_t) 0) - MASK_BITS &&
		s->root->mask == ~(mask_t) 0));

	return true;
}