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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {TYPE_1__* postfix; } ;
typedef  TYPE_2__ spl_recursive_it_object ;
struct TYPE_4__ {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETVAL_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_recursive_tree_iterator_get_postfix(spl_recursive_it_object *object, zval *return_value)
{
	RETVAL_STR(object->postfix[0].s);
	Z_ADDREF_P(return_value);
}