#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  mpz_ptr ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 TYPE_1__* GET_GMP_OBJECT_FROM_OBJ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmp_strval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zend_array_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *gmp_get_debug_info(zend_object *obj, int *is_temp) /* {{{ */
{
	HashTable *ht, *props = zend_std_get_properties(obj);
	mpz_ptr gmpnum = GET_GMP_OBJECT_FROM_OBJ(obj)->num;
	zval zv;

	*is_temp = 1;
	ht = zend_array_dup(props);

	gmp_strval(&zv, gmpnum, 10);
	zend_hash_str_update(ht, "num", sizeof("num")-1, &zv);

	return ht;
}