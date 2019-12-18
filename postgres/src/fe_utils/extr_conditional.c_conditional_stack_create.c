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
struct TYPE_4__ {int /*<<< orphan*/ * head; } ;
typedef  int /*<<< orphan*/  ConditionalStackData ;
typedef  TYPE_1__* ConditionalStack ;

/* Variables and functions */
 TYPE_1__* pg_malloc (int) ; 

ConditionalStack
conditional_stack_create(void)
{
	ConditionalStack cstack = pg_malloc(sizeof(ConditionalStackData));

	cstack->head = NULL;
	return cstack;
}