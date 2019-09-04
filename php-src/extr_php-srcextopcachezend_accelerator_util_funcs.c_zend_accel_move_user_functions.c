#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_15__ {int /*<<< orphan*/ * filename; } ;
struct TYPE_19__ {int nNumUsed; int /*<<< orphan*/ * pDestructor; TYPE_6__* arData; } ;
struct TYPE_17__ {TYPE_1__ main_op_array; TYPE_5__ function_table; } ;
typedef  TYPE_3__ zend_script ;
struct TYPE_16__ {int /*<<< orphan*/ * filename; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_2__ op_array; } ;
typedef  TYPE_4__ zend_function ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/ * dtor_func_t ;
struct TYPE_20__ {int /*<<< orphan*/  key; int /*<<< orphan*/  val; } ;
typedef  TYPE_5__ HashTable ;
typedef  TYPE_6__ Bucket ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 scalar_t__ IS_UNDEF ; 
 scalar_t__ UNEXPECTED (int) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 TYPE_4__* Z_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zend_hash_append_ptr (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  zend_hash_del_bucket (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  zend_hash_extend (TYPE_5__*,int,int /*<<< orphan*/ ) ; 

void zend_accel_move_user_functions(HashTable *src, uint32_t count, zend_script *script)
{
	Bucket *p, *end;
	HashTable *dst;
	zend_string *filename;
	dtor_func_t orig_dtor;
	zend_function *function;

	if (!count) {
		return;
	}

	dst = &script->function_table;
	filename = script->main_op_array.filename;
	orig_dtor = src->pDestructor;
	src->pDestructor = NULL;
	zend_hash_extend(dst, count, 0);
	end = src->arData + src->nNumUsed;
	p = end - count;
	for (; p != end; p++) {
		if (UNEXPECTED(Z_TYPE(p->val) == IS_UNDEF)) continue;
		function = Z_PTR(p->val);
		if (EXPECTED(function->type == ZEND_USER_FUNCTION)
		 && EXPECTED(function->op_array.filename == filename)) {
			_zend_hash_append_ptr(dst, p->key, function);
			zend_hash_del_bucket(src, p);
		}
	}
	src->pDestructor = orig_dtor;
}