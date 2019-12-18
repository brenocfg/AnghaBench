#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int /*<<< orphan*/  mpz_ptr ;

/* Variables and functions */
 int /*<<< orphan*/ * gmp_create_object_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *gmp_create_object(zend_class_entry *ce) /* {{{ */
{
	mpz_ptr gmpnum_dummy;
	return gmp_create_object_ex(ce, &gmpnum_dummy);
}