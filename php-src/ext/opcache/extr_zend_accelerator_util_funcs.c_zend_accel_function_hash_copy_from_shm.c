#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_19__ {int function_name; } ;
struct TYPE_18__ {int filename; scalar_t__ last; TYPE_1__* opcodes; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_3__ common; TYPE_2__ op_array; } ;
typedef  TYPE_4__ zend_function ;
struct TYPE_22__ {int key; int /*<<< orphan*/  val; } ;
struct TYPE_21__ {int nNumUsed; scalar_t__ nInternalPointer; TYPE_6__* arData; } ;
struct TYPE_17__ {int lineno; } ;
typedef  TYPE_5__ HashTable ;
typedef  int CG ;
typedef  TYPE_6__ Bucket ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ IS_UNDEF ; 
 scalar_t__ UNEXPECTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 scalar_t__ ZSTR_LEN (int) ; 
 scalar_t__* ZSTR_VAL (int) ; 
 TYPE_4__* Z_PTR (int /*<<< orphan*/ ) ; 
 TYPE_4__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zend_hash_append_ptr_ex (TYPE_5__*,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  zend_hash_extend (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_find_ex (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  zend_hash_update_ptr (TYPE_5__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  zend_set_compiled_filename (int) ; 

__attribute__((used)) static void zend_accel_function_hash_copy_from_shm(HashTable *target, HashTable *source)
{
	zend_function *function1, *function2;
	Bucket *p, *end;
	zval *t;

	zend_hash_extend(target, target->nNumUsed + source->nNumUsed, 0);
	p = source->arData;
	end = p + source->nNumUsed;
	for (; p != end; p++) {
		ZEND_ASSERT(Z_TYPE(p->val) != IS_UNDEF);
		ZEND_ASSERT(p->key);
		t = zend_hash_find_ex(target, p->key, 1);
		if (UNEXPECTED(t != NULL)) {
			if (EXPECTED(ZSTR_LEN(p->key) > 0) && EXPECTED(ZSTR_VAL(p->key)[0] == 0)) {
				/* Mangled key */
				zend_hash_update_ptr(target, p->key, Z_PTR(p->val));
			} else {
				goto failure;
			}
		} else {
			_zend_hash_append_ptr_ex(target, p->key, Z_PTR(p->val), 1);
		}
	}
	target->nInternalPointer = 0;
	return;

failure:
	function1 = Z_PTR(p->val);
	function2 = Z_PTR_P(t);
	CG(in_compilation) = 1;
	zend_set_compiled_filename(function1->op_array.filename);
	CG(zend_lineno) = function1->op_array.opcodes[0].lineno;
	if (function2->type == ZEND_USER_FUNCTION
		&& function2->op_array.last > 0) {
		zend_error(E_ERROR, "Cannot redeclare %s() (previously declared in %s:%d)",
				   ZSTR_VAL(function1->common.function_name),
				   ZSTR_VAL(function2->op_array.filename),
				   (int)function2->op_array.opcodes[0].lineno);
	} else {
		zend_error(E_ERROR, "Cannot redeclare %s()", ZSTR_VAL(function1->common.function_name));
	}
}