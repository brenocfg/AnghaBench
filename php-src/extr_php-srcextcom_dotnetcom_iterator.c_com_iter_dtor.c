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
struct php_com_iterator {int /*<<< orphan*/  zdata; int /*<<< orphan*/  safe_array; int /*<<< orphan*/  v; scalar_t__ ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEnumVARIANT_Release (scalar_t__) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void com_iter_dtor(zend_object_iterator *iter)
{
	struct php_com_iterator *I = (struct php_com_iterator*)Z_PTR(iter->data);

	if (I->ev) {
		IEnumVARIANT_Release(I->ev);
	}
	VariantClear(&I->v);
	VariantClear(&I->safe_array);
	zval_ptr_dtor(&I->zdata);
}