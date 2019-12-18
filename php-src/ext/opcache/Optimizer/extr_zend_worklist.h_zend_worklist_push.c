#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int capacity; } ;
struct TYPE_4__ {TYPE_2__ stack; int /*<<< orphan*/  visited; } ;
typedef  TYPE_1__ zend_worklist ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ zend_bitset_in (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_incl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_worklist_stack_push (TYPE_2__*,int) ; 

__attribute__((used)) static inline int zend_worklist_push(zend_worklist *worklist, int i)
{
	ZEND_ASSERT(i >= 0 && i < worklist->stack.capacity);

	if (zend_bitset_in(worklist->visited, i)) {
		return 0;
	}

	zend_bitset_incl(worklist->visited, i);
	zend_worklist_stack_push(&worklist->stack, i);
	return 1;
}