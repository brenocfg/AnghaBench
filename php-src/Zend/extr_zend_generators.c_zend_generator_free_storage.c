#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {int /*<<< orphan*/  ht; } ;
struct TYPE_6__ {int children; TYPE_1__ child; } ;
struct TYPE_7__ {scalar_t__ iterator; int /*<<< orphan*/  std; TYPE_2__ node; int /*<<< orphan*/  retval; int /*<<< orphan*/  key; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ zend_generator ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 scalar_t__ UNEXPECTED (int) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_generator_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_iterator_dtor (scalar_t__) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_generator_free_storage(zend_object *object) /* {{{ */
{
	zend_generator *generator = (zend_generator*) object;

	zend_generator_close(generator, 0);

	/* we can't immediately free them in zend_generator_close() else yield from won't be able to fetch it */
	zval_ptr_dtor(&generator->value);
	zval_ptr_dtor(&generator->key);

	if (EXPECTED(!Z_ISUNDEF(generator->retval))) {
		zval_ptr_dtor(&generator->retval);
	}

	if (UNEXPECTED(generator->node.children > 1)) {
		zend_hash_destroy(generator->node.child.ht);
		efree(generator->node.child.ht);
	}

	zend_object_std_dtor(&generator->std);

	if (generator->iterator) {
		zend_iterator_dtor(generator->iterator);
	}
}