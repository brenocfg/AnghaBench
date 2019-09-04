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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  std; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ gmp_object ;

/* Variables and functions */
 TYPE_1__* GET_GMP_OBJECT_FROM_OBJ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmp_free_object_storage(zend_object *obj) /* {{{ */
{
	gmp_object *intern = GET_GMP_OBJECT_FROM_OBJ(obj);

	mpz_clear(intern->num);
	zend_object_std_dtor(&intern->std);
}