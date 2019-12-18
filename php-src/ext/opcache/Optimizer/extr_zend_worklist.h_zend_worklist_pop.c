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
struct TYPE_3__ {int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ zend_worklist ;

/* Variables and functions */
 int zend_worklist_stack_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int zend_worklist_pop(zend_worklist *worklist)
{
	/* Does not clear visited flag */
	return zend_worklist_stack_pop(&worklist->stack);
}