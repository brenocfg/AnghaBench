#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {scalar_t__ name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ zend_constant ;

/* Variables and functions */
 int CONST_PERSISTENT ; 
 int ZEND_CONSTANT_FLAGS (TYPE_1__*) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int) ; 
 int /*<<< orphan*/  zval_internal_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

void free_zend_constant(zval *zv)
{
	zend_constant *c = Z_PTR_P(zv);

	if (!(ZEND_CONSTANT_FLAGS(c) & CONST_PERSISTENT)) {
		zval_ptr_dtor_nogc(&c->value);
		if (c->name) {
			zend_string_release_ex(c->name, 0);
		}
		efree(c);
	} else {
		zval_internal_ptr_dtor(&c->value);
		if (c->name) {
			zend_string_release_ex(c->name, 1);
		}
		free(c);
	}
}