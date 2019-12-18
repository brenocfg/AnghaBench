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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  Z_SPLRECURSIVE_IT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_recursive_it_move_forward_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_recursive_it_move_forward(zend_object_iterator *iter)
{
	spl_recursive_it_move_forward_ex(Z_SPLRECURSIVE_IT_P(&iter->data), &iter->data);
}