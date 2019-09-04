#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/  static_variables_ptr; } ;
struct TYPE_5__ {TYPE_1__ op_array; } ;
struct TYPE_6__ {TYPE_2__ func; } ;
typedef  TYPE_3__ zend_closure ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * ZEND_MAP_PTR_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void zend_closure_bind_var(zval *closure_zv, zend_string *var_name, zval *var) /* {{{ */
{
	zend_closure *closure = (zend_closure *) Z_OBJ_P(closure_zv);
	HashTable *static_variables = ZEND_MAP_PTR_GET(closure->func.op_array.static_variables_ptr);
	zend_hash_update(static_variables, var_name, var);
}