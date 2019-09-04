#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_uchar ;
typedef  int zend_long ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_12__ {scalar_t__ kind; scalar_t__ size; TYPE_2__ array; TYPE_1__ pointer; } ;
typedef  TYPE_3__ zend_ffi_type ;
struct TYPE_13__ {char* ptr; int /*<<< orphan*/  type; int /*<<< orphan*/  std; } ;
typedef  TYPE_4__ zend_ffi_cdata ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_OBJECT ; 
 int /*<<< orphan*/  OBJ_RELEASE (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 scalar_t__ ZEND_ADD ; 
 TYPE_3__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_TYPE_ARRAY ; 
 scalar_t__ ZEND_FFI_TYPE_POINTER ; 
 scalar_t__ ZEND_SUB ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_add (TYPE_4__*,TYPE_3__*,int) ; 
 scalar_t__ zend_ffi_cdata_ce ; 
 scalar_t__ zend_ffi_is_same_type (TYPE_3__*,TYPE_3__*) ; 
 int zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zend_ffi_cdata_do_operation(zend_uchar opcode, zval *result, zval *op1, zval *op2) /* {{{ */
{
	zend_long offset;

	ZVAL_DEREF(op1);
	ZVAL_DEREF(op2);
	if (Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == zend_ffi_cdata_ce) {
		zend_ffi_cdata *cdata1 = (zend_ffi_cdata*)Z_OBJ_P(op1);
		zend_ffi_type *type1 = ZEND_FFI_TYPE(cdata1->type);

		if (type1->kind == ZEND_FFI_TYPE_POINTER || type1->kind == ZEND_FFI_TYPE_ARRAY) {
			if (opcode == ZEND_ADD) {
				offset = zval_get_long(op2);
				ZVAL_OBJ(result, zend_ffi_add(cdata1, type1, offset));
				if (result == op1) {
					OBJ_RELEASE(&cdata1->std);
				}
				return SUCCESS;
			} else if (opcode == ZEND_SUB) {
				if (Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == zend_ffi_cdata_ce) {
					zend_ffi_cdata *cdata2 = (zend_ffi_cdata*)Z_OBJ_P(op2);
					zend_ffi_type *type2 = ZEND_FFI_TYPE(cdata2->type);

					if (type2->kind == ZEND_FFI_TYPE_POINTER || type2->kind == ZEND_FFI_TYPE_ARRAY) {
						zend_ffi_type *t1, *t2;
						char *p1, *p2;

						if (type1->kind == ZEND_FFI_TYPE_POINTER) {
							t1 = ZEND_FFI_TYPE(type1->pointer.type);
							p1 = (char*)(*(void**)cdata1->ptr);
						} else {
							t1 = ZEND_FFI_TYPE(type1->array.type);
							p1 = cdata1->ptr;
						}
						if (type2->kind == ZEND_FFI_TYPE_POINTER) {
							t2 = ZEND_FFI_TYPE(type2->pointer.type);
							p2 = (char*)(*(void**)cdata2->ptr);
						} else {
							t2 = ZEND_FFI_TYPE(type2->array.type);
							p2 = cdata2->ptr;
						}
						if (zend_ffi_is_same_type(t1, t2)) {
							ZVAL_LONG(result,
								(zend_long)(p1 - p2) / (zend_long)t1->size);
							return SUCCESS;
						}
					}
				}
				offset = zval_get_long(op2);
				ZVAL_OBJ(result, zend_ffi_add(cdata1, type1, -offset));
				if (result == op1) {
					OBJ_RELEASE(&cdata1->std);
				}
				return SUCCESS;
			}
		}
	} else if (Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == zend_ffi_cdata_ce) {
		zend_ffi_cdata *cdata2 = (zend_ffi_cdata*)Z_OBJ_P(op2);
		zend_ffi_type *type2 = ZEND_FFI_TYPE(cdata2->type);

		if (type2->kind == ZEND_FFI_TYPE_POINTER || type2->kind == ZEND_FFI_TYPE_ARRAY) {
			if (opcode == ZEND_ADD) {
				offset = zval_get_long(op1);
				ZVAL_OBJ(result, zend_ffi_add(cdata2, type2, offset));
				return SUCCESS;
			}
		}
	}

	return FAILURE;
}