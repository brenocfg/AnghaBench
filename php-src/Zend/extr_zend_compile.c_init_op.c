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
struct TYPE_4__ {int /*<<< orphan*/  lineno; scalar_t__ extended_value; } ;
typedef  TYPE_1__ zend_op ;

/* Variables and functions */
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_lineno ; 

__attribute__((used)) static void init_op(zend_op *op)
{
	MAKE_NOP(op);
	op->extended_value = 0;
	op->lineno = CG(zend_lineno);
}