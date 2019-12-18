#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  entry; } ;
struct TYPE_5__ {int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ STACK ;
typedef  TYPE_2__ FORMSTR ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stack_push(STACK *stack, FORMSTR *str)
{
    list_add_head(&stack->items, &str->entry);
}