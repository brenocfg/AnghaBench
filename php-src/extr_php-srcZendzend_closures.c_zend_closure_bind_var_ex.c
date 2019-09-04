#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  static_variables_ptr; } ;
struct TYPE_7__ {TYPE_1__ op_array; } ;
struct TYPE_8__ {TYPE_2__ func; } ;
typedef  TYPE_3__ zend_closure ;
typedef  int uint32_t ;
struct TYPE_9__ {scalar_t__ arData; } ;
typedef  TYPE_4__ HashTable ;

/* Variables and functions */
 TYPE_4__* ZEND_MAP_PTR_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void zend_closure_bind_var_ex(zval *closure_zv, uint32_t offset, zval *val) /* {{{ */
{
	zend_closure *closure = (zend_closure *) Z_OBJ_P(closure_zv);
	HashTable *static_variables = ZEND_MAP_PTR_GET(closure->func.op_array.static_variables_ptr);
	zval *var = (zval*)((char*)static_variables->arData + offset);
	zval_ptr_dtor(var);
	ZVAL_COPY_VALUE(var, val);
}