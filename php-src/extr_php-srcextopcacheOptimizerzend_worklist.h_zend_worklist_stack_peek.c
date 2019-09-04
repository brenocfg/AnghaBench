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
struct TYPE_3__ {int len; int* buf; } ;
typedef  TYPE_1__ zend_worklist_stack ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 

__attribute__((used)) static inline int zend_worklist_stack_peek(zend_worklist_stack *stack)
{
	ZEND_ASSERT(stack->len);
	return stack->buf[stack->len - 1];
}