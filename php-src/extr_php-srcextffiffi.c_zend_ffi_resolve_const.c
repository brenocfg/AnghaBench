#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* str; size_t len; int /*<<< orphan*/  kind; int /*<<< orphan*/  i64; } ;
typedef  TYPE_2__ zend_ffi_val ;
struct TYPE_8__ {scalar_t__ kind; TYPE_1__* type; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ zend_ffi_symbol ;
struct TYPE_6__ {int kind; } ;

/* Variables and functions */
 scalar_t__ FFI_G (int /*<<< orphan*/ ) ; 
 scalar_t__ UNEXPECTED (scalar_t__) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_SYM_CONST ; 
#define  ZEND_FFI_TYPE_SINT16 135 
#define  ZEND_FFI_TYPE_SINT32 134 
#define  ZEND_FFI_TYPE_SINT64 133 
#define  ZEND_FFI_TYPE_SINT8 132 
#define  ZEND_FFI_TYPE_UINT16 131 
#define  ZEND_FFI_TYPE_UINT32 130 
#define  ZEND_FFI_TYPE_UINT64 129 
#define  ZEND_FFI_TYPE_UINT8 128 
 int /*<<< orphan*/  ZEND_FFI_VAL_ERROR ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_INT32 ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_INT64 ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_NAME ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_UINT32 ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_UINT64 ; 
 int /*<<< orphan*/  attribute_parsing ; 
 int /*<<< orphan*/  symbols ; 
 TYPE_3__* zend_hash_str_find_ptr (scalar_t__,char const*,size_t) ; 

void zend_ffi_resolve_const(const char *name, size_t name_len, zend_ffi_val *val) /* {{{ */
{
	zend_ffi_symbol *sym;

	if (UNEXPECTED(FFI_G(attribute_parsing))) {
		val->kind = ZEND_FFI_VAL_NAME;
		val->str = name;
		val->len = name_len;
		return;
	} else if (FFI_G(symbols)) {
		sym = zend_hash_str_find_ptr(FFI_G(symbols), name, name_len);
		if (sym && sym->kind == ZEND_FFI_SYM_CONST) {
			val->i64 = sym->value;
			switch (sym->type->kind) {
				case ZEND_FFI_TYPE_SINT8:
				case ZEND_FFI_TYPE_SINT16:
				case ZEND_FFI_TYPE_SINT32:
					val->kind = ZEND_FFI_VAL_INT32;
					break;
				case ZEND_FFI_TYPE_SINT64:
					val->kind = ZEND_FFI_VAL_INT64;
					break;
				case ZEND_FFI_TYPE_UINT8:
				case ZEND_FFI_TYPE_UINT16:
				case ZEND_FFI_TYPE_UINT32:
					val->kind = ZEND_FFI_VAL_UINT32;
					break;
				case ZEND_FFI_TYPE_UINT64:
					val->kind = ZEND_FFI_VAL_UINT64;
					break;
				default:
					ZEND_ASSERT(0);
			}
			return;
		}
	}
	val->kind = ZEND_FFI_VAL_ERROR;
}